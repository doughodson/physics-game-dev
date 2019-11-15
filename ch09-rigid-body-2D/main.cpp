
#include "main.h"
#include "time.h"

//---------------------------------------------------------------------------
/*
Book:           
Authors:        
Example:        
*/
//---------------------------------------------------------------------------


// Global Variables:
int				FrameCounter = 0;
RigidBody2D		Craft; 
RigidBody2D		Craft2;

#define		_TIMESTEP		0.001
#define		_TOL			1e-10
#define		_FWDTIME		10


bool	Initialize(void)
{
	
	Craft.vPosition.x = _WINWIDTH/10;
	Craft.vPosition.y = _WINHEIGHT/2;
	Craft.fOrientation = 0;//270;

	//  ch10
	Craft2.vPosition.x = _WINWIDTH/2;
	Craft2.vPosition.y = _WINHEIGHT/2;
	Craft2.fOrientation = 90;
	
	return true;
}


void	UpdateSimulation(void)
{
	double	dt = _TIMESTEP;
	//RECT	r;
	
	Craft.SetThrusters(false, false);
	
	if (IsKeyDown(VK_UP))
		Craft.ModulateThrust(true);
	
	if (IsKeyDown(VK_DOWN))
		Craft.ModulateThrust(false);
		
	if (IsKeyDown(VK_RIGHT))
		Craft.SetThrusters(true, false);

	if (IsKeyDown(VK_LEFT))
		Craft.SetThrusters(false, true);

	// update the simulation 
	Craft.UpdateBodyEuler(dt);
	
	// ch10
	Craft2.UpdateBodyEuler(dt);

	if(FrameCounter >= _RENDER_FRAME_COUNT)
	{			
		// update the display
		ClearBackBuffer();

		DrawCraft(Craft, RGB(0,0,255));

		// ch 10
		DrawCraft(Craft2, RGB(200, 200, 0));

		CopyBackBufferToWindow();
		FrameCounter = 0;
	} else
		FrameCounter++;

	if(Craft.vPosition.x > _WINWIDTH) Craft.vPosition.x = 0;
	if(Craft.vPosition.x < 0) Craft.vPosition.x = _WINWIDTH;
	if(Craft.vPosition.y > _WINHEIGHT) Craft.vPosition.y = 0;
	if(Craft.vPosition.y < 0) Craft.vPosition.y = _WINHEIGHT;

	// Ch10
	if(Craft2.vPosition.x > _WINWIDTH) Craft2.vPosition.x = 0;
	if(Craft2.vPosition.x < 0) Craft2.vPosition.x = _WINWIDTH;
	if(Craft2.vPosition.y > _WINHEIGHT) Craft2.vPosition.y = 0;
	if(Craft2.vPosition.y < 0) Craft2.vPosition.y = _WINHEIGHT;


}

void	DrawCraft(RigidBody2D	craft, COLORREF clr)
{
	Vector	vList[5];
	double	wd, lg;
	int		i;
	Vector	v1;

	wd = craft.fWidth;
	lg = craft.fLength;
	vList[0].x = lg/2;	vList[0].y = wd/2;
	vList[1].x = -lg/2;	vList[1].y = wd/2;
	vList[2].x = -lg/2;	vList[2].y = -wd/2;
	vList[3].x = lg/2;	vList[3].y = -wd/2;
	vList[4].x = lg/2*1.5; vList[4].y = 0;
	for(i=0; i<5; i++)
	{
		v1 = VRotate2D(craft.fOrientation, vList[i]);
		vList[i] = v1 + craft.vPosition;			
	}

	DrawLine(vList[0].x, vList[0].y, vList[1].x, vList[1].y, 2, clr);
	DrawLine(vList[1].x, vList[1].y, vList[2].x, vList[2].y, 2, clr);
	DrawLine(vList[2].x, vList[2].y, vList[3].x, vList[3].y, 2, clr);
	DrawLine(vList[3].x, vList[3].y, vList[4].x, vList[4].y, 2, clr);
	DrawLine(vList[4].x, vList[4].y, vList[0].x, vList[0].y, 2, clr);


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
