
#ifndef __physics_HPP__
#define __physics_HPP__

#include "physics.hpp"
#include "particle.hpp"

// Windows Header Files
#include <windows.h>
#include <windef.h>
#include <commctrl.h>
#include <commdlg.h>
#include <wingdi.h> 

#define _WINWIDTH  1024
#define _WINHEIGHT 768

#define _TIMESTEP        0.1
#define _TOL             1e-10
#define _FWDTIME         10
#define _MAX_NUM_UNITS   1000
#define _OBSTACLE_RADIUS 20
#define _NUM_OBSTACLES   15
#define _SPAWN_AREA_R    50
#define _GROUND_PLANE    100
#define _COLLISION_TOL   1

#define _RENDER_FRAME_COUNT 1

void ClearBackBuffer();
void DrawLine(int x1, int y1, int x2, int y2, int thk, COLORREF clr);
void CopyBackBufferToWindow();

extern int FrameCounter;
extern Particle Units[];
extern Particle Obstacles[];

bool Initialize();
void UpdateSimulation();
bool CheckForCollisions(Particle* p);
void DrawObstacles();
int GetRandomNumber(int min, int max, bool seed);

#endif
