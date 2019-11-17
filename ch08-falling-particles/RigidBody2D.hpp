
#ifndef __RigidBody2D_HPP__
#define __RigidBody2D_HPP__

#include "common/Vector.hpp"

#define _THRUSTFORCE              20.0f/2.0
#define _MAXTHRUST                80.0f/2.0
#define _MINTHRUST                 0.0f
#define _DTHRUST                   0.01f
#define _STEERINGFORCE             6.0f
#define _LINEARDRAGCOEFFICIENT     0.3f
#define _ANGULARDRAGCOEFFICIENT 5000.0f

//------------------------------------------------------------------------
// Classs: RigidBody2D
// Description: 2D rigid body structure
//------------------------------------------------------------------------
class RigidBody2D
{
public:
   RigidBody2D() = default;
   void CalcLoads();
   void UpdateBodyEuler(double dt);
   void SetThrusters(bool p, bool s);
   void ModulateThrust(bool up);

	float	fMass;             // total mass (constant)
	float	fInertia;          // mass moment of inertia in body coordinates (constant)
	float	fInertiaInverse;   // inverse of mass moment of inertia (constant)
	
	Vector vPosition;        // position in earth coordinates
	Vector vVelocity;        // velocity in earth coordinates
	Vector vVelocityBody;    // velocity in body coordinates
	Vector vAngularVelocity; // angular velocity in body coordinates
		
	float fSpeed;            // speed (magnitude of the velocity)
	float fOrientation;      // orientation 	

	Vector vForces;          // total force on body
	Vector vMoment;          // total moment (torque) on body (2D: about z-axis only)

	float	ThrustForce;       // Magnitude of the thrust force
	Vector PThrust, SThrust; // bow thruster forces

	float	fWidth;            // bounding dimensions
	float	fLength;
	float	fHeight;

	Vector CD;
	Vector CT;
	Vector CPT;
	Vector CST;

   float ProjectedArea;

   Vector Fa;  // other applied force
   Vector Pa;  // location of other applied force

   //Vector	vCollisionPoint;  // point of impact in local coordinates	
};

#endif
