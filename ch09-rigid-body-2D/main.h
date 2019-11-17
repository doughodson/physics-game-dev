#ifndef _MAINHEADER
#define _MAINHEADER

#include "winmain.h"
#include "RigidBody2D.hpp"

#define	_RENDER_FRAME_COUNT		330

void UpdateSimulation(void);
bool Initialize(void);
void DrawCraft(RigidBody2D	craft, COLORREF clr);
int GetRandomNumber(int min, int max, bool seed);


#endif