#ifndef __BourgFDM_HPP__
#define __BourgFDM_HPP__

#include "RigidBody.hpp"
#include "BodyElement.hpp"

#include "common/Vector.hpp"
#include "common/Matrix3x3.hpp"
#include "common/Quaternion.hpp"

//------------------------------------------------------------------------------
// Class: BourgFDM
// Description: Behavior of a rigid body as defined in Bourg book
//------------------------------------------------------------------------------
// Notes:
//------------------------------------------------------------------------------
//  Earth coordinates: x points North
//                     y points West
//                     z points up
//
//
//                Z   X
//                |  /
//                | /
//                |/
//                Y------+
//
//
// Body coordinates: x points to the front
//                   y points to left
//                   z points up 
//
// Units: English system,
//          distance     --> feet
//          time         --> seconds
//          mass         --> slugs
//          force        --> pounds
//          moment       --> foot-pounds
//          velocity     --> feet-per-second
//          acceleration --> feet-per-second^2
//          density      --> slugs-per-feet^3
//------------------------------------------------------------------------------
class BourgFDM : public RigidBody
{
public:
   BourgFDM();

   void calc_mass_properties();          // calcs total mass and inertia
   void calc_loads();                    // calcs total forces and moments
   void step_simulation(const float dt); // step dt time in the simulation
   Vector getBodyZAxisVector();
   Vector getBodyXAxisVector();
   void inc_thrust();
   void dec_thrust();
   void left_rudder();
   void right_rudder();
   void zero_rudder();
   void roll_left();
   void roll_right();
   void pitch_up();
   void pitch_down();
   void zero_ailerons();
   void zero_elevators();
   void flaps_down();
   void zero_flaps();

   BodyElement element[8];  // Mass, inertia and lifting surface properties of our airplane
   Vector thrust;           // Thrust vector, assumed to act through the plane's CG
   float thrust_force{};    // Magnitude of the thrust force
   bool stalling{};         // Flag to let us know if we are in a stalled condition
   bool flaps{};            // Flag to let us know if the flaps are down

private:
   Matrix3x3 make_angular_velocity_matrix(Vector u);
   float lift_coefficient(const float angle, const int flaps);
   float drag_coefficient(const float angle, const int flaps);
   float rudder_lift_coefficient(const float angle);
   float rudder_drag_coefficient(const float angle);
};

#endif
