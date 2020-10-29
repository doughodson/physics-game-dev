#ifndef __RigidBody_HPP__
#define __RigidBody_HPP__

#include "common/Vector.hpp"
#include "common/Matrix3x3.hpp"
#include "common/Quaternion.hpp"

//------------------------------------------------------------------------------
// Class: RigidBody
// Description: Data that defines a rigid body
//------------------------------------------------------------------------------
class RigidBody
{
public:
   RigidBody() = default;

   float fMass{};             // total mass (constant)
   Matrix3x3 mInertia;        // mass moment of inertia in body coordinates (constant)
   Matrix3x3 mInertiaInverse; // inverse of mass moment of inertia matrix	(constant)

   Vector vPosition;          // position in earth coordinates
   Vector vVelocity;          // velocity in earth coordinates
   Vector vVelocityBody;      // velocity in body coordinates
   Vector vAngularVelocity;   // angular velocity in body coordinates
   Vector vEulerAngles;       // Euler angles in body coordinates
   float fSpeed{};            // speed (magnitude of the velocity)

   Quaternion qOrientation;   // orientation in earth coordinates
   //Matrix3x3 mRotation;     // rotation matrix

   Vector vForces;            // total force on body
   Vector vMoments;           // total moment (torque) on body

   Matrix3x3 mIeInverse;      // inverse of moment of inertia in earth coordinates

// testing...
   Vector p1, p2;
// ... end testing

};

#endif
