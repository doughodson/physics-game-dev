
//---------------------------------------------------------------------------
/*
Book:           Physics for Game Developers, 2nd Edition
Authors:        David M. Bourg, Bryan Bywalec, Kenneth Humphreys
Example:        Realtime Particle Simulation, Chapter 8, Example 1
*/
//---------------------------------------------------------------------------

#include "physics.hpp"
#include "time.h"
#include "particle.hpp"

// Windows Header Files
#include <windows.h>
#include <windef.h>
#include <commctrl.h>
#include <commdlg.h>
#include <wingdi.h> 

// global variables
int FrameCounter{};
Particle Units[_MAX_NUM_UNITS]{};
Particle Obstacles[_NUM_OBSTACLES]{};

bool Initialize()
{
    GetRandomNumber(0, _WINWIDTH, true);
			
    for (int i{}; i<_MAX_NUM_UNITS; i++) {
        Units[i].vPosition.x = GetRandomNumber(_WINWIDTH/2-_SPAWN_AREA_R*2, _WINWIDTH/2+_SPAWN_AREA_R*2, false);
        Units[i].vPosition.y = _WINHEIGHT - GetRandomNumber(0, _SPAWN_AREA_R, false);
    }

    for (int i{}; i<_NUM_OBSTACLES; i++) {
        Obstacles[i].vPosition.x = GetRandomNumber(_WINWIDTH/2 - _OBSTACLE_RADIUS*10, _WINWIDTH/2+_OBSTACLE_RADIUS*10, false);
        Obstacles[i].vPosition.y = GetRandomNumber(_GROUND_PLANE+_OBSTACLE_RADIUS, _WINHEIGHT/2-_OBSTACLE_RADIUS*4, false);
        Obstacles[i].fRadius = _OBSTACLE_RADIUS;
        Obstacles[i].fMass = 100;
    }
    return true;
}

void UpdateSimulation()
{
	double dt{_TIMESTEP};
	
	// initialize the back buffer
	if (FrameCounter >= _RENDER_FRAME_COUNT) {
		ClearBackBuffer();
		// Draw ground plane
		DrawLine(0, _WINHEIGHT - _GROUND_PLANE, _WINWIDTH, _WINHEIGHT - _GROUND_PLANE, 3, RGB(0,0,0));
		DrawObstacles();

	}

	// update computer controlled units:	
	for (int i{}; i<_MAX_NUM_UNITS; i++) {
		Units[i].bCollision = CheckForCollisions(&(Units[i]));	
		Units[i].CalcLoads();
		Units[i].UpdateBodyEuler(dt);

		if (FrameCounter >= _RENDER_FRAME_COUNT) {
			Units[i].Draw();
		}

		if(Units[i].vPosition.x > _WINWIDTH) Units[i].vPosition.x = 0;
		if(Units[i].vPosition.x < 0) Units[i].vPosition.x = _WINWIDTH;
		//if(Units[i].vPosition.y < 0) Units[i].vPosition.y = _WINHEIGHT;		
	} // end i-loop	

	if (FrameCounter >= _RENDER_FRAME_COUNT) {
		CopyBackBufferToWindow();
		FrameCounter = 0;
	}  else {
		FrameCounter++;
   }
}

bool CheckForCollisions(Particle* p)
{
    Vector n;              // collision normal
    Vector vr;             // relative velocity
    float vrn;
    float J;               // impulse
    Vector Fi;             // impact force vector
    bool hasCollision{};

    // reset aggregate impact force
    p->vImpactForces.x = 0;
    p->vImpactForces.y = 0;

    // check for collisions with ground plane
    // check for penetration through ground plane
    if (p->vPosition.y <= (_GROUND_PLANE+p->fRadius)) {
        n.x = 0;
        n.y = 1;
        vr = p->vVelocity;
        vrn = vr * n;
        if (vrn < 0.0) {
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

    for (int i{}; i<_NUM_OBSTACLES; i++) {
        r = p->fRadius + Obstacles[i].fRadius;
        d = p->vPosition - Obstacles[i].vPosition;
        s = d.magnitude() - r;

        if (s <= _COLLISION_TOL) {
            d.normalize();
            n = d;
            vr = p->vVelocity - Obstacles[i].vVelocity;
            vrn = vr*n;

            if (vrn < 0.0) {
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
	for(int i{}; i<_NUM_OBSTACLES; i++) {
		Obstacles[i].Draw();
	}
}

int GetRandomNumber(int min, int max, bool seed)
{
    if (seed)
        srand( (unsigned)time( NULL ) );

    int number{(((abs(rand())%(max-min+1))+min))};

    if (number>max) number = max;
    if (number<min) number = min;
		
	return number;
}


