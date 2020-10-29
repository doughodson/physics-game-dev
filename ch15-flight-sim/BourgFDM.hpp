#ifndef __BourgFDM_HPP__
#define __BourgFDM_HPP__

#include "RigidBody.hpp"
#include "BodyElement.hpp"

#include "common/Vector.hpp"
#include "common/Matrix3x3.hpp"
#include "common/Quaternion.hpp"

//------------------------------------------------------------------------
// Notes:
//------------------------------------------------------------------------
//
//
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
// Note:  Direct3D's coordinates system is a left handed one with the z-axis pointing
//        into the screen, the x-axis pointing to the right and the y-axis pointing up
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
//
//

//------------------------------------------------------------------------------
// Class: BourgFDM
// Description: Behavior of a rigid body as defined in Bourg book
//------------------------------------------------------------------------------
class BourgFDM : public RigidBody
{
public:
   BourgFDM();

   void CalcAirplaneMassProperties();   // calcs total mass and inertia
   void CalcAirplaneLoads();            // calcs total forces and moments
   void StepSimulation(const float dt); // step dt time in the simulation
   Vector GetBodyZAxisVector();
   Vector GetBodyXAxisVector();
   Matrix3x3 MakeAngularVelocityMatrix(Vector u);
   float LiftCoefficient(const float angle, const int flaps);
   float DragCoefficient(const float angle, const int flaps);
   float RudderLiftCoefficient(const float angle);
   float RudderDragCoefficient(const float angle);
   void IncThrust();
   void DecThrust();
   void LeftRudder();
   void RightRudder();
   void ZeroRudder();
   void RollLeft();
   void RollRight();
   void PitchUp();
   void PitchDown();
   void ZeroAilerons();
   void ZeroElevators();
   void FlapsDown();
   void ZeroFlaps();

//private:

   BodyElement Element[8];  // Mass, inertia and lifting surface properties of our airplane
   Vector Thrust;           // Thrust vector, assumed to act through the plane's CG
   float ThrustForce{};     // Magnitude of the thrust force
   bool Stalling{};         // Flag to let us know if we are in a stalled condition
   bool Flaps{};            // Flag to let us know if the flaps are down
};

#endif
