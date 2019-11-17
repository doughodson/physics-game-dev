
#include "RigidBody2D.hpp"

#include "common/math_utils.hpp"

RigidBody2D::RigidBody2D()
{
	fMass = 100;
	fInertia = 500;
	fInertiaInverse = 1/fInertia;
	vPosition.x = 0;
	vPosition.y = 0;
	fWidth = 10;
	fLength = 20;
	fHeight = 5;
	fOrientation = 0;	
	CD.x = -0.25*fLength;		
	CD.y = 0.0f;
	
	CT.x = -0.5*fLength;		
	CT.y = 0.0f;
	
	CPT.y = -0.5*fLength;		
	CPT.x = 0.5*fWidth;
	
	CST.y = 0.5*fLength;		
	CST.x = 0.5*fWidth;

	ProjectedArea = (fLength + fWidth) * fHeight;
	ThrustForce = _THRUSTFORCE;
}

void RigidBody2D::CalcLoads(void)
{
	Vector	Fb;				// stores the sum of forces
	Vector	Mb;				// stores the sum of moments
	Vector	Thrust;			// thrust vector
	
	// reset forces and moments:
	vForces.x = 0.0f;
	vForces.y = 0.0f;
	vForces.z = 0.0f;	// always zero in 2D

	vMoment.x = 0.0f;	// always zero in 2D
	vMoment.y = 0.0f;	// always zero in 2D
	vMoment.z = 0.0f;

	Fb.x = 0.0f;	
	Fb.y = 0.0f;	
	Fb.z = 0.0f;	

	Mb.x = 0.0f;
	Mb.y = 0.0f;
	Mb.z = 0.0f;

	// Define the thrust vector, which acts through the craft's CG
	Thrust.x = 1.0f;
	Thrust.y = 0.0f;
	Thrust.z = 0.0f;  // zero in 2D
	Thrust *= ThrustForce;
	
	// Calculate forces and moments in body space:
	Vector	vLocalVelocity;
	float	fLocalSpeed;
	Vector	vDragVector;	
	float	tmp;
	Vector	vResultant;	
	Vector	vtmp;	

	// Calculate the aerodynamic drag force:
		// Calculate local velocity:
		// The local velocity includes the velocity due to linear motion of the craft, 
		// plus the velocity at each element due to the rotation of the craft.
		vtmp = vAngularVelocity^CD; // rotational part
		vLocalVelocity = vVelocityBody + vtmp; 

		// Calculate local air speed
		fLocalSpeed = vLocalVelocity.magnitude();

		// Find the direction in which drag will act.
		// Drag always acts inline with the relative velocity but in the opposing direction
		if(fLocalSpeed > tol) 
		{
			vLocalVelocity.normalize();
			vDragVector = -vLocalVelocity;		

			// Determine the resultant force on the element.
			tmp = 0.5f * rho * fLocalSpeed*fLocalSpeed * ProjectedArea;		
			vResultant = vDragVector * _LINEARDRAGCOEFFICIENT * tmp;

			// Keep a running total of these resultant forces (total force)
			Fb += vResultant;
		
			// Calculate the moment about the CG of this element's force
			// and keep a running total of these moments (total moment)
			vtmp = CD^vResultant; 
			Mb += vtmp;
		}

		// Calculate the Port & Starboard bow thruster forces:
		// Keep a running total of these resultant forces (total force)
		Fb += PThrust;
		

		// Calculate the moment about the CG of this element's force
		// and keep a running total of these moments (total moment)
		vtmp = CPT^PThrust; 
		Mb += vtmp;

		// Keep a running total of these resultant forces (total force)
		Fb += SThrust;

		// Calculate the moment about the CG of this element's force
		// and keep a running total of these moments (total moment)
		vtmp = CST^SThrust; 		
		Mb += vtmp;

	// Now add the propulsion thrust
	Fb += Thrust; // no moment since line of action is through CG

	// Convert forces from model space to earth space
	vForces = VRotate2D(fOrientation, Fb);

	vMoment += Mb;	
}

void RigidBody2D::UpdateBodyEuler(double dt)
{
		Vector a;
		Vector dv;
		Vector ds;
		float  aa;
		float  dav;
		float  dr;
	
		// Calculate forces and moments:
		CalcLoads();
		
		// Integrate linear equation of motion:
		a = vForces / fMass;
		
		dv = a * dt;
		vVelocity += dv;

		ds = vVelocity * dt;
		vPosition += ds;

		// Integrate angular equation of motion:
		aa = vMoment.z / fInertia;

		dav = aa * dt;
		
		vAngularVelocity.z += dav;
		
		dr = RadiansToDegrees(vAngularVelocity.z * dt);
		fOrientation += dr; 
		
		// Misc. calculations:
		fSpeed = vVelocity.magnitude();		
		vVelocityBody = VRotate2D(-fOrientation, vVelocity);	
}

void RigidBody2D::SetThrusters(bool p, bool s)
{
	PThrust.x = 0;
	PThrust.y = 0;
	SThrust.x = 0;
	SThrust.y = 0;
	
	if(p)
		PThrust.y = _STEERINGFORCE;
	if(s)
		SThrust.y = -_STEERINGFORCE;
}

void RigidBody2D::ModulateThrust(bool up)
{
	const double dT = up ? _DTHRUST:-_DTHRUST;

	ThrustForce += dT;

	if(ThrustForce > _MAXTHRUST) ThrustForce = _MAXTHRUST;
	if(ThrustForce < _MINTHRUST) ThrustForce = _MINTHRUST;
}



