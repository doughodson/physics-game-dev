//---------------------------------------------------------------------------
// Book:    Physics for Game Developers, 2nd Edition
// Authors: David M. Bourg, Bryan Bywalec, Kenneth Humphreys
// Example: Realtime Particle Simulation, Chapter 8, Example 1
//---------------------------------------------------------------------------

#include "Particle.h"
#include "winmain.h"

Particle::Particle()
{
	fMass = 1.0;				
	vPosition.x = 0.0;
	vPosition.y = 0.0;
	vPosition.z = 0.0;
	vVelocity.x = 0.0;
	vVelocity.y = 0.0;
	vVelocity.z = 0.0;
	fSpeed = 0.0;						
	vForces.x = 0.0;
	vForces.y = 0.0;
	vForces.z = 0.0;
	fRadius = 0.1f;					
	vGravity.x = 0;
	vGravity.y = fMass * _GRAVITYACCELERATION; 
	vPreviousPosition = vPosition;
}

void Particle::CalcLoads()
{
	// Reset forces:
	vForces.x = 0.0f;
	vForces.y = 0.0f;
	
	// Aggregate forces:
	if(bCollision) {
		// Add Impact forces (if any)
		vForces += vImpactForces;
	} else {
		// Gravity
		vForces += vGravity;

		// Still air drag
		Vector	vDrag;
		float	fDrag;
		vDrag-=vVelocity;
		vDrag.Normalize();
		fDrag = static_cast<float>(0.5 * _AIRDENSITY * fSpeed * fSpeed * (3.14159 * fRadius * fRadius) * _DRAGCOEFFICIENT);
		vDrag*=fDrag;

		vForces += vDrag;

		// Wind
		Vector	vWind;
		vWind.x = static_cast<float>(0.5 * _AIRDENSITY * _WINDSPEED * _WINDSPEED * (3.14159 * fRadius * fRadius) * _DRAGCOEFFICIENT);
		vForces += vWind;
	}
}

void Particle::UpdateBodyEuler(const double dt)
{
   // Save the previous position
   vPreviousPosition = vPosition; 

   // Integrate equation of motion:
   Vector a = vForces / fMass;
		
   Vector dv = a * dt;
   vVelocity += dv;

   Vector ds = vVelocity * dt;
   vPosition += ds;
	
   // Misc. calculations:
   fSpeed = vVelocity.Magnitude();		
}

void Particle::Draw()
{
	RECT	r;
	float	drawRadius = max(2, fRadius);

	SetRect(&r, vPosition.x - drawRadius, _WINHEIGHT - (vPosition.y - drawRadius), vPosition.x + drawRadius, _WINHEIGHT - (vPosition.y + drawRadius));
	DrawEllipse(&r, 2, RGB(0,0,255));

	if (ShowVectors) {
		Vector	v, u;
		double	f{0.025};

		// Show velocity vectors in green
		DrawLine(vPosition.x, vPosition.y, vPosition.x + vVelocity.x, vPosition.y + vVelocity.y, 3, RGB(0,255,0));
	}

}
