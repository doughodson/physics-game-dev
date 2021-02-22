
#ifndef __particle_HPP__
#define __particle_HPP__

#include "common/Vector.hpp"

#define _GRAVITYACCELERATION -9.8f  // Acceleration due to gravity in m/s^2
#define _DRAGCOEFFICIENT      0.6f  // Nondimensional drag coefficient 
#define _AIRDENSITY           1.23f // Density of at at 15C in kg/m^3
#define _WINDSPEED            0.1f  // Wind speed in m/s (10 m/s is almost 20 knots)
#define _RESTITUTION          0.2f  // Coefficient of restitution

//------------------------------------------------------------------------
// Class: Particle
// Description: Structure of a particle
//------------------------------------------------------------------------
class Particle
{
public:
   Particle();

   void CalcLoads();                      // aggregates all the forces acting on the particle
   void UpdateBodyEuler(const double dt); // integrates one time step updating velocity and position
   void Draw();                           // draws the particle

	float	fMass{1.0f};        // total mass
	Vector vPosition;         // position 
	Vector vVelocity;	        // velocity
	float fSpeed{};           // speed (magnitude of the velocity)
	Vector vForces;           // total force acting on the particle
	float fRadius{0.1f};      // radius of particle used for collision detection
	Vector vGravity;          // gravity force vector
	Vector vPreviousPosition; // position at previous time step (used for collision detection)
	Vector vImpactForces;     // used to aggregate collision impact forces
	bool bCollision{};
};

#endif
