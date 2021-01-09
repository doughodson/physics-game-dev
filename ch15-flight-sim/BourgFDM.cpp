
#include "BourgFDM.hpp"

#include "BodyElement.hpp"
#include "common/Vector.hpp"

#include <cmath>

#define _DTHRUST     10.0f
#define _MAXTHRUST 3000.0f

//------------------------------------------------------------------------
// constructor that defines the initial state of an airplane which
// includes:
//   initial location, and speed, along with its thrust and attitude
//   and mass properties
//------------------------------------------------------------------------
BourgFDM::BourgFDM()
{
   // initial position
   position = Vector(-5000.0f, 0.0f, 2000.0f);
   // initial velocity
   velocity = Vector(60.0f, 0.0f, 0.0f);
   speed = 60.0f;

   // initial angular velocity
   angular_velocity = Vector(0.0f, 0.0f, 0.0f);

   // initial thrust, force and moment
   force = Vector(500.0f, 0.0f, 0.0f);
   thrust_force = 500.0;

   moment = Vector(0.0f, 0.0f, 0.0f);

   // zero the velocity in body space coordinates
   velocity_body = Vector(0.0f, 0.0f, 0.0f);

   // not stallings and no flaps
   stalling = false;
   flaps = false;

   // initial orientation
   const float iRoll{}, iPitch{}, iYaw{};
   orientation = MakeQFromEulerAngles(iRoll, iPitch, iYaw);

   // calculate mass properties
   calc_mass_properties();
}

//------------------------------------------------------------------------
// update model using Euler's method
//------------------------------------------------------------------------
void BourgFDM::update(const float dt)
{
   //----------------------
   // compute translation
   //----------------------

   // calculate all of the forces and moments on the airplane
   calc_loads();

   // calculate the acceleration of the airplane in earth space
   Vector Ae{force / mass};

   // calculate the velocity of the airplane in earth space
   velocity += Ae * dt;

   // calculate the position of the airplane in earth space
   position += velocity * dt;

   //----------------------
   // compute rotation
   //----------------------

   // testing...
   angular_velocity += inertia_inverse * (moment - (angular_velocity^(inertia * angular_velocity))) * dt;

   // update the rotation quaternion:
   orientation += (orientation * angular_velocity) * (0.5f * dt);

   // normalize the orientation quaternion
   const float mag{orientation.magnitude()};
   if (mag != 0.0f) {
      orientation /= mag;
   }

   // calculate the velocity in body space
   // (we'll need this to calculate lift and drag forces)
   velocity_body = QVRotate(~orientation, velocity);

   // calculate the air speed
   speed = velocity.magnitude();

   // get the Euler angles for our information
   Vector u{MakeEulerAnglesFromQ(orientation)};
   euler_angles.x = u.x;  // roll
   euler_angles.y = u.y;  // pitch
   euler_angles.z = u.z;  // yaw
}

//------------------------------------------------------------------------
//  update model using modified Euler's method -- midpoint method
//------------------------------------------------------------------------
void BourgFDM::update2(const float dt)
{
   //----------------------
   // compute translation
   //----------------------

   // calculate all of the forces and moments on the airplane
   calc_loads();

   // calculate the acceleration of the airplane in earth space
   Vector Ae{force / mass};

   // calculate the velocity of the airplane in earth space
   Vector Vdot{Ae * (dt/2.0f)};
   Vector Pdot{velocity + Vdot * (dt/2.0f)};

   velocity += Vdot * dt;

   // calculate the position of the airplane in earth space
   position += Pdot * dt;

   //----------------------
   // compute rotation
   //----------------------

   // make a matrix out of the angular velocity vector
   Matrix3x3 mAngularVelocity{make_angular_velocity_matrix(angular_velocity)};

   // calculate the angular velocity of the airplane in body space
   angular_velocity += inertia_inverse * (moment - mAngularVelocity * inertia * angular_velocity) * dt;

   // calculate the new rotation quaternion
   orientation += (orientation * angular_velocity) * (0.5f * dt);

   // now normalize the orientation quaternion:
   float mag{orientation.magnitude()};
   if (mag != 0.0f) {
      orientation /= mag;
   }

   // calculate the velocity in body space:
   // (we'll need this to calculate lift and drag forces)
   velocity_body = QVRotate(~orientation, velocity);

   // calculate the air speed:
   speed = velocity.magnitude();

   // get the Euler angles for our information
   Vector u{MakeEulerAnglesFromQ(orientation)};
   euler_angles.x = u.x;  // roll
   euler_angles.y = u.y;  // pitch
   euler_angles.z = u.z;  // yaw
}

//------------------------------------------------------------------------
//   This model uses a set of eight descrete elements to represent the 
//   airplane.  The elements are described below:
//
//   Element 1: Outboard, Port (left) wing section fitted with ailerons
//   Element 2: Inboard, Port wing section fitted with landing flaps
//   Element 3: Inboard, Starboard (right) wing section fitted with landing flaps
//   Element 4: Outboard, Starboard wing section fitted with ailerons
//   Element 5: Port elevator fitted with flap
//   Element 6: Starboard elevator fitted with flap
//   Element 7: Vertical tail/rudder (no flap the whole thing rotates)
//   Element 8: The fuselage
//
//	  This function first sets up each element and then goes on to calculate
//   the combined weight, center of gravity, and inertia tensor for the plane.
//   Some other properties of each element are also calculated which you'll
//   need when calculating the lift and drag forces on the plane.
//------------------------------------------------------------------------
void BourgFDM::calc_mass_properties()
{
   // Initialize the elements here
   // Initially the coordinates of each element are referenced from
   // a design coordinates system located at the very tail end of the plane,
   // its baseline and center line.  Later, these coordinates will be adjusted
   // so that each element is referenced to the combined center of gravity of
   // the airplane
   element[0].mass = 6.56f;
   element[0].dsg_coord = Vector(14.5f, 12.0f, 2.5f);
   element[0].local_inertia = Vector(13.92f, 10.50f, 24.00f);
   element[0].incidence_angle = -3.5f;
   element[0].dihedral_angle = 0.0f;
   element[0].area = 31.2f;
   element[0].flap = 0;

   element[1].mass = 7.31f;
   element[1].dsg_coord = Vector(14.5f, 5.5f, 2.5f);
   element[1].local_inertia = Vector(21.95f, 12.22f, 33.67f);
   element[1].incidence_angle = -3.5f;
   element[1].dihedral_angle = 0.0f;
   element[1].area = 36.4f;
   element[1].flap = 0;

   element[2].mass = 7.31f;
   element[2].dsg_coord = Vector(14.5f, -5.5f, 2.5f);
   element[2].local_inertia = Vector(21.95f, 12.22f, 33.67f);
   element[2].incidence_angle = -3.5f;
   element[2].dihedral_angle = 0.0f;
   element[2].area = 36.4f;
   element[2].flap = 0;

   element[3].mass = 6.56f;
   element[3].dsg_coord = Vector(14.5f, -12.0f, 2.5f);
   element[3].local_inertia = Vector(13.92f, 10.50f, 24.00f);
   element[3].incidence_angle = -3.5f;
   element[3].dihedral_angle = 0.0f;
   element[3].area = 31.2f;
   element[3].flap = 0;

   element[4].mass = 2.62f;
   element[4].dsg_coord = Vector(3.03f, 2.5f, 3.0f);
   element[4].local_inertia = Vector(0.837f, 0.385f, 1.206f);
   element[4].incidence_angle = 0.0f;
   element[4].dihedral_angle = 0.0f;
   element[4].area = 10.8f;
   element[4].flap = 0;

   element[5].mass = 2.62f;
   element[5].dsg_coord = Vector(3.03f, -2.5f, 3.0f);
   element[5].local_inertia = Vector(0.837f,0.385f, 1.206f);
   element[5].incidence_angle = 0.0f;
   element[5].dihedral_angle = 0.0f;
   element[5].area = 10.8f;
   element[5].flap = 0;

   element[6].mass = 2.93f;
   element[6].dsg_coord = Vector(2.25f, 0.0f, 5.0f);
   element[6].local_inertia = Vector(1.262f, 1.942f, 0.718f);
   element[6].incidence_angle = 0.0f;
   element[6].dihedral_angle = 90.0f;
   element[6].area = 12.0f;
   element[6].flap = 0;

   element[7].mass = 31.8f;
   element[7].dsg_coord = Vector(15.25f, 0.0f, 1.5f);
   element[7].local_inertia = Vector(66.30f, 861.9f, 861.9f);
   element[7].incidence_angle = 0.0f;
   element[7].dihedral_angle = 0.0f;
   element[7].area = 84.0f;
   element[7].flap = 0;

   // determine the vector normal (perpendicular) to each lifting surface (this is
   // required when calculating the relative air velocity for lift and drag calculations)
   for (int i{}; i< 8; i++) {
      float in{DegreesToRadians(element[i].incidence_angle)};
      float di{DegreesToRadians(element[i].dihedral_angle)};
      element[i].normal = Vector(static_cast<float>(std::sin(in)),
                                  static_cast<float>(std::cos(in) * std::sin(di)),
                                  static_cast<float>(std::cos(in) * std::cos(di)));
      element[i].normal.normalize();
   }

   // update total mass
   mass = 0.0f;
   for (int i{}; i< 8; i++) {
      mass += element[i].mass;
   }

   // calculate combined center of gravity location
   Vector vMoment;
   for (int i{}; i< 8; i++) {
      vMoment += element[i].mass * element[i].dsg_coord;
   }
   Vector CG = vMoment/mass;

   // calculate coordinates of each element with respect to the combined CG 
   for (int i{}; i< 8; i++) {
      element[i].cg_coord = element[i].dsg_coord - CG;
   }

   // calculate the moments and products of inertia for the combined elements
   // (This inertia matrix (tensor) is in body coordinates)
   float Ixx{}, Iyy{}, Izz{}, Ixy{}, Ixz{}, Iyz{};
   for (int i{}; i< 8; i++) {
      Ixx += element[i].local_inertia.x + 
             element[i].mass * (element[i].cg_coord.y * element[i].cg_coord.y + element[i].cg_coord.z * element[i].cg_coord.z);
      Iyy += element[i].local_inertia.y +
             element[i].mass * (element[i].cg_coord.z * element[i].cg_coord.z + element[i].cg_coord.x * element[i].cg_coord.x);
      Izz += element[i].local_inertia.z +
             element[i].mass * (element[i].cg_coord.x * element[i].cg_coord.x + element[i].cg_coord.y * element[i].cg_coord.y);
      Ixy += element[i].mass * (element[i].cg_coord.x * element[i].cg_coord.y);
      Ixz += element[i].mass * (element[i].cg_coord.x * element[i].cg_coord.z);
      Iyz += element[i].mass * (element[i].cg_coord.y * element[i].cg_coord.z);
   }

   // setup mass and its inertia matrix and take the inverse of the inertia matrix
   inertia.e11 = Ixx;  inertia.e12 = -Ixy; inertia.e13 = -Ixz;
   inertia.e21 = -Ixy; inertia.e22 = Iyy;  inertia.e23 = -Iyz;
   inertia.e31 = -Ixz; inertia.e32 = -Iyz; inertia.e33 = Izz;

   inertia_inverse = inertia.inverse();
}

//------------------------------------------------------------------------
// calculates all of the forces and moments acting on the plane
// at any given time
//------------------------------------------------------------------------
void BourgFDM::calc_loads()
{
   // reset forces and moments
   force = Vector(0.0f, 0.0f, 0.0f);
   moment = Vector(0.0f, 0.0f, 0.0f);

   Vector Fb;   // total force
   Vector Mb;   // total moment

   // define the thrust vector, which acts through the plane's CG
   Vector thrust(1.0f, 0.0f, 0.0f);
   thrust *= thrust_force;

   // calculate forces and moments in body space
   Vector vDragVector;

   stalling = false;

   for(int i{}; i<8; i++) { // loop through the seven lifting elements skipping the fuselage
      if (i == 6) {         // The tail/rudder is a special case since it can rotate
                            // thus you have to recalculate the normal vector
         float in{DegreesToRadians(element[i].incidence_angle)};  // incidence angle
         float di{DegreesToRadians(element[i].dihedral_angle)};   // dihedral angle
         element[i].normal = Vector(static_cast<float>(std::sin(in)), 
                                    static_cast<float>(std::cos(in) * std::sin(di)),
                                    static_cast<float>(std::cos(in) * std::cos(di)));     // surface normal vector
         element[i].normal.normalize();
      }

      // determine local velocity at element (the local velocity includes the
      // velocity due to linear motion of the airplane, plus the velocity at
      // each element due to the rotation of the airplane
      Vector vtmp{angular_velocity^element[i].cg_coord}; // rotational part
      Vector vLocalVelocity{velocity_body + vtmp};

      // calculate local air speed
      float fLocalSpeed{vLocalVelocity.magnitude()};

      // determine direction in which drag will act (drag always acts inline
      // with the relative velocity but in the opposing direction
      if (fLocalSpeed > 1.0) {
         vDragVector = -vLocalVelocity/fLocalSpeed;
      }

      // determine direction in which lift will act (lift is
      // always perpendicular to the drag vector
      Vector vLiftVector{(vDragVector^element[i].normal)^vDragVector};
      float tmp{vLiftVector.magnitude()};
      vLiftVector.normalize();

      // determine angle of attack (the angle between the lift vector and the
      // element normal vector) Note: the sine of the attack angle, is equal
      // to the cosine of the angle between the drag vector and the normal vector
      tmp = vDragVector * element[i].normal;
      if (tmp > 1.) tmp = 1;
      if (tmp < -1) tmp = -1;
      float fAttackAngle{RadiansToDegrees(static_cast<float>(std::asin(tmp)))};

      // determine the resultant force (lift and drag) on the element
      tmp = 0.5f * rho * fLocalSpeed*fLocalSpeed * element[i].area;		
      Vector vResultant;
      if (i == 6) { // Tail/rudder
         vResultant = (vLiftVector * rudder_lift_coefficient(fAttackAngle) +
                       vDragVector * rudder_drag_coefficient(fAttackAngle) ) * tmp;
      } else if (i == 7) {
         vResultant = vDragVector * 0.5f * tmp; // simulate fuselage drag
      } else {
         vResultant = (vLiftVector * lift_coefficient(fAttackAngle, element[i].flap) +
                       vDragVector * drag_coefficient(fAttackAngle, element[i].flap) ) * tmp;
      }
      // determine when stalled by noting when the coefficient of lift is zero
      if (i<=3) {
         if (lift_coefficient(fAttackAngle, element[i].flap) == 0) {
            stalling = true;
         }
      }

      // keep a running total of these resultant forces (total force)
      Fb += vResultant;

      // calculate the moment about the CG of this element's force
      // and keep a running total of these moments (total moment)
      vtmp = element[i].cg_coord^vResultant;
      Mb += vtmp;
   }

   // add the thrust
   Fb += thrust;

   // convert force from model space to earth space
   force = QVRotate(orientation, Fb);

   // apply gravity (g is defined as -32.174 ft/s^2)
   force.z += g * mass;

   moment += Mb;
}

Vector BourgFDM::get_body_Z_axis_vector()
{
   Vector v(0.0f, 0.0f, 1.0f);
   return QVRotate(orientation, v);
}

Vector BourgFDM::get_body_X_axis_vector()
{
   Vector v(1.0f, 0.0f, 0.0f);
   return QVRotate(orientation, v);
}

Matrix3x3 BourgFDM::make_angular_velocity_matrix(const Vector& u)
{
   return Matrix3x3( 0.0f, -u.z, u.y,
                     u.z, 0.0f, -u.x,
                    -u.y, u.x, 0.0f);
}

//------------------------------------------------------------------------
// given the attack angle and the status of the flaps, this function
// returns the appropriate lift coefficient for a cambered airfoil with
// a plain trailing edge flap (+/- 15 degree deflection)
//------------------------------------------------------------------------
float BourgFDM::lift_coefficient(const float angle, const int flaps)
{
   float clf0[9] = {-0.54f, -0.2f, 0.2f, 0.57f, 0.92f, 1.21f, 1.43f, 1.4f, 1.0f};
   float clfd[9] = {0.0f, 0.45f, 0.85f, 1.02f, 1.39f, 1.65f, 1.75f, 1.38f, 1.17f};
   float clfu[9] = {-0.74f, -0.4f, 0.0f, 0.27f, 0.63f, 0.92f, 1.03f, 1.1f, 0.78f};
   float a[9]    = {-8.0f, -4.0f, 0.0f, 4.0f, 8.0f, 12.0f, 16.0f, 20.0f, 24.0f};

   float cl{};
   for (int i{}; i<8; i++) {
      if ( (a[i] <= angle) && (a[i+1] > angle) ) {
         switch (flaps) {
            case 0:// flaps not deflected
               cl = clf0[i] - (a[i] - angle) * (clf0[i] - clf0[i+1]) / (a[i] - a[i+1]);
               break;
            case -1: // flaps down
               cl = clfd[i] - (a[i] - angle) * (clfd[i] - clfd[i+1]) / (a[i] - a[i+1]);
               break;
            case 1: // flaps up
               cl = clfu[i] - (a[i] - angle) * (clfu[i] - clfu[i+1]) / (a[i] - a[i+1]);
               break;
         }
         break;
      }
   }
   return cl;
}

//------------------------------------------------------------------------
// given the attack angle and the status of the flaps, this function
// returns the appropriate drag coefficient for a cambered airfoil with
// a plain trailing edge flap (+/- 15 degree deflection)
//------------------------------------------------------------------------
float BourgFDM::drag_coefficient(const float angle, const int flaps)
{
   const float cdf0[9] = {0.01f, 0.0074f, 0.004f, 0.009f, 0.013f, 0.023f, 0.05f, 0.12f, 0.21f};
   const float cdfd[9] = {0.0065f, 0.0043f, 0.0055f, 0.0153f, 0.0221f, 0.0391f, 0.1f, 0.195f, 0.3f};
   const float cdfu[9] = {0.005f, 0.0043f, 0.0055f, 0.02601f, 0.03757f, 0.06647f, 0.13f, 0.18f, 0.25f};
   const float a[9]    = {-8.0f, -4.0f, 0.0f, 4.0f, 8.0f, 12.0f, 16.0f, 20.0f, 24.0f};

   float cd{0.75};
   for (int i{}; i<8; i++) {
      if ( (a[i] <= angle) && (a[i+1] > angle) ) {
         switch (flaps) {
            case 0:  // flaps not deflected
               cd = cdf0[i] - (a[i] - angle) * (cdf0[i] - cdf0[i+1]) / (a[i] - a[i+1]);
               break;
            case -1: // flaps down
               cd = cdfd[i] - (a[i] - angle) * (cdfd[i] - cdfd[i+1]) / (a[i] - a[i+1]);
               break;
            case 1: // flaps up
               cd = cdfu[i] - (a[i] - angle) * (cdfu[i] - cdfu[i+1]) / (a[i] - a[i+1]);
               break;
         }
         break;
      }
   }
   return cd;
}

//------------------------------------------------------------------------
// given the attack angle this function returns the proper lift coefficient
// for a symmetric (no camber) airfoil without flaps
//------------------------------------------------------------------------
float BourgFDM::rudder_lift_coefficient(const float angle)
{
   const float clf0[7] = {0.16f, 0.456f, 0.736f, 0.968f, 1.144f, 1.12f, 0.8f};
   const float a[7]    = {0.0f, 4.0f, 8.0f, 12.0f, 16.0f, 20.0f, 24.0f};
   const float aa{static_cast<float>(std::fabs(angle))};

   float cl{};
   for (int i{}; i<6; i++) {
      if ( (a[i] <= aa) && (a[i+1] > aa) ) {
         cl = clf0[i] - (a[i] - aa) * (clf0[i] - clf0[i+1]) / (a[i] - a[i+1]);
         if (angle < 0) cl = -cl;
         break;
      }
   }
   return cl;
}

//------------------------------------------------------------------------
// given the attack angle this function returns the proper drag coefficient
// for a symmetric (no camber) airfoil without flaps
//------------------------------------------------------------------------
float BourgFDM::rudder_drag_coefficient(const float angle)
{
   const float cdf0[7] = {0.0032f, 0.0072f, 0.0104f, 0.0184f, 0.04f, 0.096f, 0.168f};
   const float a[7]    = {0.0f, 4.0f, 8.0f, 12.0f, 16.0f, 20.0f, 24.0f};
   const float aa{static_cast<float>(std::fabs(angle))};

   float cd{0.75f};
   for (int i{}; i<6; i++) {
      if ( (a[i] <= aa) && (a[i+1] > aa) ) {
         cd = cdf0[i] - (a[i] - aa) * (cdf0[i] - cdf0[i+1]) / (a[i] - a[i+1]);
         break;
      }
   }
   return cd;
}

void BourgFDM::inc_thrust()
{
   thrust_force += _DTHRUST;
   if (thrust_force > _MAXTHRUST) {
      thrust_force = _MAXTHRUST;
   }
}

void BourgFDM::dec_thrust()
{
   thrust_force -= _DTHRUST;
   if (thrust_force < 0) {
      thrust_force = 0;
   }
}

void BourgFDM::left_rudder()
{
   element[6].incidence_angle = 16;
}

void BourgFDM::right_rudder()
{
   element[6].incidence_angle = -16;
}

void BourgFDM::zero_rudder()
{
   element[6].incidence_angle = 0;
}

void BourgFDM::roll_left()
{
   element[0].flap = 1;
   element[3].flap = -1;
}

void BourgFDM::roll_right()
{
   element[0].flap = -1;
   element[3].flap = 1;
}

void BourgFDM::pitch_up()
{
   element[4].flap = 1;
   element[5].flap = 1;
}

void BourgFDM::pitch_down()
{
   element[4].flap = -1;
   element[5].flap = -1;
}

void BourgFDM::zero_ailerons()
{
   element[0].flap = 0;
   element[3].flap = 0;
}

void BourgFDM::zero_elevators()
{
   element[4].flap = 0;
   element[5].flap = 0;
}

void BourgFDM::flaps_down()
{
   element[1].flap = -1;
   element[2].flap = -1;
   flaps = true;
}

void BourgFDM::zero_flaps()
{
   element[1].flap = 0;
   element[2].flap = 0;
   flaps = false;
}
