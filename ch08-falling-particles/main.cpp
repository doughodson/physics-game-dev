#include "main.h"
#include "time.h"
//---------------------------------------------------------------------------
/*
Book:           Physics for Game Developers, 2nd Edition
Authors:        David M. Bourg, Bryan Bywalec, Kenneth Humphreys
Example:        Realtime Particle Simulation, Chapter 8, Example 1
*/
//---------------------------------------------------------------------------

#define		_TIMESTEP						0.1
#define		_TOL							1e-10
#define		_FWDTIME						10
#define		_MAX_NUM_UNITS					1000
#define		_OBSTACLE_RADIUS				20
#define		_NUM_OBSTACLES					15
#define		_SPAWN_AREA_R					50
#define		_GROUND_PLANE					100
#define		_COLLISION_TOL					1

// Global Variables:
int				FrameCounter = 0;
Particle		Units[_MAX_NUM_UNITS];
Particle		Obstacles[_NUM_OBSTACLES];

bool	Initialize(void)
{
	int i;

	GetRandomNumber(0, _WINWIDTH, true);
			
	for(i=0; i<_MAX_NUM_UNITS; i++)
	{	
		Units[i].vPosition.x = GetRandomNumber(_WINWIDTH/2-_SPAWN_AREA_R*2, _WINWIDTH/2+_SPAWN_AREA_R*2, false);
		Units[i].vPosition.y = _WINHEIGHT - GetRandomNumber(0, _SPAWN_AREA_R, false);
	}

	for(i=0; i<_NUM_OBSTACLES; i++)
	{
		Obstacles[i].vPosition.x = GetRandomNumber(_WINWIDTH/2 - _OBSTACLE_RADIUS*10, _WINWIDTH/2+_OBSTACLE_RADIUS*10, false);
		Obstacles[i].vPosition.y = GetRandomNumber(_GROUND_PLANE+_OBSTACLE_RADIUS, _WINHEIGHT/2-_OBSTACLE_RADIUS*4, false);
		Obstacles[i].fRadius = _OBSTACLE_RADIUS;
		Obstacles[i].fMass = 100;

	}

	return true;
}

void	UpdateSimulation(void)
{
	double	dt = _TIMESTEP;
	int		i;
	
	// initialize the back buffer
	if(FrameCounter >= _RENDER_FRAME_COUNT)
	{
		ClearBackBuffer();
		// Draw ground plane
		DrawLine(0, _WINHEIGHT - _GROUND_PLANE, _WINWIDTH, _WINHEIGHT - _GROUND_PLANE, 3, RGB(0,0,0));
		DrawObstacles();

	}

	// update computer controlled units:	
	for(i=0; i<_MAX_NUM_UNITS; i++)
	{	
		Units[i].bCollision = CheckForCollisions(&(Units[i]));	
		Units[i].CalcLoads();
		Units[i].UpdateBodyEuler(dt);

		if(FrameCounter >= _RENDER_FRAME_COUNT)
		{
			Units[i].Draw();
		}

		if(Units[i].vPosition.x > _WINWIDTH) Units[i].vPosition.x = 0;
		if(Units[i].vPosition.x < 0) Units[i].vPosition.x = _WINWIDTH;
		//if(Units[i].vPosition.y < 0) Units[i].vPosition.y = _WINHEIGHT;		
	} // end i-loop	

	if(FrameCounter >= _RENDER_FRAME_COUNT) {
		CopyBackBufferToWindow();
		FrameCounter = 0;
	}  else
		FrameCounter++;
}

bool	CheckForCollisions(Particle* p)
{
	int		i;
	Vector	n; // collision normal
	Vector  vr; // relative velocity
	float  vrn;
	float	J;  // Impulse
	Vector	Fi; // impact force vector
	bool	hasCollision = false;


		// Reset aggregate impact force
		p->vImpactForces.x = 0;
		p->vImpactForces.y = 0;

		// check for collisions with ground plane
		// check for penetration through ground plane
		if(p->vPosition.y <= (_GROUND_PLANE+p->fRadius)) {
			n.x = 0;
			n.y = 1;
			vr = p->vVelocity;
			vrn = vr * n;
			if(vrn < 0.0) {
				J = -(vr*n) * (_RESTITUTION + 1) * p->fMass;
				Fi = n;
				Fi*=J/_TIMESTEP;
				p->vImpactForces+=Fi;

				p->vPosition.y = _GROUND_PLANE+p->fRadius;
				p->vPosition.x = (_GROUND_PLANE+p->fRadius-p->vPreviousPosition.y) / (p->vPosition.y - p->vPreviousPosition.y) * (p->vPosition.x - p->vPreviousPosition.x) + p->vPreviousPosition.x;

				hasCollision = true;
			}
		}
		

		// check for collisions with obstacles
		// check for penetration through obstacles 
		// must check the case for one unit passing completely through another
		float r;
		Vector d;
		float s;

		for(i=0; i<_NUM_OBSTACLES; i++)
		{
				r = p->fRadius + Obstacles[i].fRadius;
				d = p->vPosition - Obstacles[i].vPosition;
				s = d.Magnitude() - r;

				if(s <= _COLLISION_TOL)
				{
					d.Normalize();
					n = d;
					vr = p->vVelocity - Obstacles[i].vVelocity;
					vrn = vr*n;
					
					if(vrn < 0.0)
					{
						J = -(vr*n) * (_RESTITUTION + 1) /(1/p->fMass + 1/Obstacles[i].fMass);
						Fi = n;
						Fi*=J/_TIMESTEP;
						p->vImpactForces+=Fi;

						p->vPosition -= n*s;

						hasCollision = true;
					}
				}
		}

	// return penetration state
	return hasCollision;
}

void DrawObstacles(void)
{
	int		i;

	for(i=0; i<_NUM_OBSTACLES; i++)
	{
		
		Obstacles[i].Draw();
	}

}

int GetRandomNumber(int min, int max, bool seed)
{
	int	number;	

	if(seed)
		srand( (unsigned)time( NULL ) );
		
    number = (((abs(rand())%(max-min+1))+min));    
    
    if(number>max)
		number = max;

    if(number<min)
    	number = min;
		
	return number;
}


