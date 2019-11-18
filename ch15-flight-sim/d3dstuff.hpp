
#include "d3drmwin.h"
#include <windows.h>

// C RunTime Header Files
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <d3drm.h>
#include <direct.h>
#include <d3dtypes.h>

// NOTE: D3D uses a left handed coordinate system.

#define RELEASE(x) if (x != NULL) {x->Release(); x = NULL;}

typedef struct _d3dInfo
{
   LPDIRECT3DRM D3DRM;
   LPDIRECTDRAWCLIPPER DDClipper;

   LPDIRECT3DRMFRAME Scene, Camera;
   LPDIRECT3DRMDEVICE Device;
   LPDIRECT3DRMVIEWPORT View;
   D3DRMCOLORMODEL Model;

   LPDIRECT3DRMFRAME Camera2;
   LPDIRECT3DRMFRAME Camera3;
} d3dInfo;

typedef struct _texInfo
{
   D3DVALUE power{};
   D3DVALUE su{};
   D3DVALUE sv{};
   D3DRMWRAPTYPE type{};
} texInfo;

BOOL CreateD3DRMObject();
BOOL CreateD3DRMClipperObject(const HWND hwnd);
BOOL CreateViewPort(const HWND hwnd);
BOOL CreateDevice(const HWND hwnd);
BOOL CreateScene();
BOOL Render();

void CleanUp();

BOOL SetupSceneLights();
BOOL LoadBackground();
BOOL LoadObject(LPDIRECT3DRMFRAME fr, char *ftex, char *fname, float sx, float sy, float sz, float x, float y, float z, BOOL makechild);
HRESULT LoadTexture(char *name, void *arg, LPDIRECT3DRMTEXTURE *tex);

void MoveCamera(const float d);
void StraifCamera(const float d);

void GetCameraDirectionAndUp(D3DVECTOR* dir, D3DVECTOR* up);
void GetCameraPosition(D3DVECTOR* pos);
void GetCameraUnitVectors(D3DVECTOR* vx, D3DVECTOR* vy, D3DVECTOR* vz);
void NormalizeVector(D3DVECTOR* v);

void YawCameraBy(const float ar);
void PitchCameraBy(const float ar);
void RollCameraBy(const float ar);

void SetCameraOrientation(float dx, float dy, float dz, float ux, float uy, float uz);

BOOL LoadObjectOnCameraFrame(char *fname, float sx, float sy, float sz, float x, float y, float z);
void SetCameraPosition(const float x, const float y, const float z);

void SetCamera1();
void SetCamera2();
void SetCamera3();

