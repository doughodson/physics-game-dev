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

   float mass{};              // total mass (constant)
   Matrix3x3 inertia;         // mass moment of inertia in body coordinates (constant)
   Matrix3x3 inertia_inverse; // inverse of mass moment of inertia matrix	(constant)

   Vector position;           // position in earth coordinates
   Vector velocity;           // velocity in earth coordinates
   Vector velocity_body;      // velocity in body coordinates
   Vector angular_velocity;   // angular velocity in body coordinates
   Vector euler_angles;       // Euler angles in body coordinates
   float speed{};             // speed (magnitude of the velocity)

   Quaternion orientation;    // orientation in earth coordinates

   Vector force;              // total force on body
   Vector moment;             // total moment (torque) on body

   Matrix3x3 mIeInverse;      // inverse of moment of inertia in earth coordinates
};

#endif
