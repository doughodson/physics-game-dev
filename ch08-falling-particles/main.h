#ifndef _MAINHEADER
#define _MAINHEADER

#include "winmain.h"
#include "mymath.h"
#include "particle.h"

#define	_RENDER_FRAME_COUNT		1

void	UpdateSimulation(void);
bool	Initialize(void);
void	DrawObstacles(void);
int		GetRandomNumber(int min, int max, bool seed);
bool	CheckForCollisions(Particle* p);

#endif