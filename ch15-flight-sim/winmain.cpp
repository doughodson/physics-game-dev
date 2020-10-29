
#define INITGUID

#define APPNAME "Flight Sim"

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <windows.h>
//#include <stdio.h>
//#include <string.h>
#include <malloc.h>
//#include <math.h>
#include "mmsystem.h"

#include <cstring>
#include <cstdio>

#include "d3dstuff.hpp"
#include "BourgFDM.hpp"

#define RENDER_FRAME_COUNT 300

// globals
HINSTANCE hInst;            // current instance
int nShowCmd;               // current show command
char szAppName[] = APPNAME; // The name of this application
char szTitle[]   = APPNAME; // The title bar text
HWND hTheMainWindow;

DWORD OldTime, NewTime;
float dt;

BOOL Initialized = false;
float TotalTime = 0;
int FrameCounter = RENDER_FRAME_COUNT;

// foward declaration of functions
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void NullEvent();
BOOL IsKeyDown(short KeyCode);

BourgFDM fdm;
extern d3dInfo D3D;
extern LPDIRECT3DRMWINDEVICE WinDev;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, const int nCmdShow)
{
   MSG msg;
   HANDLE hAccelTable;

   if (!hPrevInstance) {
      // Perform instance initialization:
      if (!InitApplication(hInstance)) {
         return (FALSE);
      }
   }

   // Perform application initialization:
   if (!InitInstance(hInstance, nCmdShow)) {
      return (FALSE);
   }

   hAccelTable = LoadAccelerators (hInstance, szAppName);

   OldTime = timeGetTime();
   NewTime = OldTime;
   // message loop
   while (true) {
      while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
         if (msg.message == WM_QUIT) {
            return msg.wParam;
         }
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

      if (Initialized)
         NullEvent();
   }

   return (msg.wParam);

   lpCmdLine; // This will prevent 'unused formal parameter' warnings
}

BOOL InitApplication(HINSTANCE hInstance)
{
   WNDCLASS wc;
   HWND hwnd;

   hwnd = FindWindow (szAppName, NULL);
   if (hwnd) {
      if (IsIconic(hwnd)) {
         ShowWindow(hwnd, SW_RESTORE);
      }
      SetForegroundWindow (hwnd);

      return FALSE;
   }

   wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
   wc.lpfnWndProc   = (WNDPROC)WndProc;
   wc.cbClsExtra    = 0;
   wc.cbWndExtra    = 0;
   wc.hInstance     = hInstance;
   wc.hIcon         = NULL;                                  // LoadIcon (hInstance, MAKEINTRESOURCE(IDI_MAINICON));
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);           // NULL
   wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);   // (HBRUSH)(COLOR_WINDOW+1);
   wc.lpszMenuName = NULL; // MAKEINTRESOURCE(IDR_MAINMENU); // "MAINMENU";
   wc.lpszClassName = szAppName;

   return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   nShowCmd = nCmdShow;

    hTheMainWindow = CreateWindow(szAppName,
                                  szTitle,
                                  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                                  0, 0, 640, 480,
                                  NULL, NULL, hInst, NULL);

   if (!CreateD3DRMObject())
      return (FALSE);

   if (!CreateD3DRMClipperObject(hTheMainWindow))
      return (FALSE);

   if (!CreateViewPort(hTheMainWindow))
      return (FALSE);

   ShowWindow(hTheMainWindow, nCmdShow);
   UpdateWindow(hTheMainWindow);

   Initialized = true;
   TotalTime = 0;

   return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   int wmId, wmEvent;
   BOOL validmenu = FALSE;
   int selection =0;
   PAINTSTRUCT ps;
   HDC pDC;
   WPARAM key;

   switch (message) {
      case WM_ACTIVATE:
         if (SUCCEEDED(D3D.Device->QueryInterface(IID_IDirect3DRMWinDevice, (void **) &WinDev))) {
            if (FAILED(WinDev->HandleActivate(wParam)))
               WinDev->Release();
         }
         break;

      case WM_COMMAND:
         wmId    = LOWORD(wParam);
         wmEvent = HIWORD(wParam);
         return (0);
         break;

      case WM_DESTROY:
         CleanUp();
         PostQuitMessage(0);
         break;

      case WM_KEYUP:
         break;

      case WM_KEYDOWN:
         key = (int) wParam;

         if (key == 0x31) // 1
            SetCamera1();

         if (key == 0x32) // 2
            SetCamera2();

         if (key == 0x33) // 3
            SetCamera3();

         break;

      case WM_PAINT:
         pDC = BeginPaint(hTheMainWindow, (LPPAINTSTRUCT) &ps);
         if (SUCCEEDED(D3D.Device->QueryInterface(IID_IDirect3DRMWinDevice, (void **) &WinDev))) {
            if (FAILED(WinDev->HandlePaint(ps.hdc)))
               WinDev->Release();
         }

         EndPaint(hTheMainWindow, (LPPAINTSTRUCT) &ps);
         return (0);
         break;

      default:
         return (DefWindowProc(hWnd, message, wParam, lParam));
   }
   return (0);
}

void NullEvent()
{
   fdm.ZeroRudder();
   fdm.ZeroAilerons();
   fdm.ZeroElevators();

   // pitch down
   if (IsKeyDown(VK_UP))
      fdm.PitchDown();

   // pitch up
   if (IsKeyDown(VK_DOWN))
      fdm.PitchUp();

   // roll left
   if (IsKeyDown(VK_LEFT))
      fdm.RollLeft();

   // roll right
   if (IsKeyDown(VK_RIGHT))
      fdm.RollRight();

   //  Increase thrust
   if (IsKeyDown(0x41)) // A
      fdm.IncThrust();

   //  Decrease thrust
   if (IsKeyDown(0x5A)) // Z
      fdm.DecThrust();

   // yaw left
   if (IsKeyDown(0x58)) // x
      fdm.LeftRudder();

   // yaw right
   if (IsKeyDown(0x43)) // c
      fdm.RightRudder();

   // landing flaps down
   if (IsKeyDown(0x46)) //f
      fdm.FlapsDown();

   // landing flaps up
   if (IsKeyDown(0x44)) // d
      fdm.ZeroFlaps();

   NewTime = timeGetTime();	
   dt = static_cast<float>((NewTime - OldTime)/1000);
   OldTime = NewTime;

   if (dt > (0.016f)) dt = (0.016f);
   if (dt < 0.001f) dt = 0.001f;

   Sleep(0.9);
   TotalTime += dt;
   //if(TotalTime > 1.6f)
   fdm.StepSimulation(dt);

   if (FrameCounter >= RENDER_FRAME_COUNT) {
      // Direct3D x = - our y
      // Direct3D y = our z
      // Direct3D z = our x
      SetCameraPosition(-fdm.vPosition.y, fdm.vPosition.z, fdm.vPosition.x);

      Vector vz{fdm.GetBodyZAxisVector()}; // pointing up in our coordinate system
      Vector vx{fdm.GetBodyXAxisVector()}; // pointing forward in our coordinate system
      SetCameraOrientation( -vx.y, vx.z, vx.x,
                            -vz.y, vz.z, vz.x);
      Render();
      FrameCounter = 0;

      //OldTime = NewTime;

      // Report stats in window title
      char buf[256];
      char s[256];
      std::sprintf(buf, "Roll= %.2f ; ", fdm.vEulerAngles.x);
      std::strcpy(s, buf);
      std::sprintf(buf, "Pitch= %.2f ; ", -fdm.vEulerAngles.y); // take negative here since pilots like to see positive pitch as nose up
      std::strcat(s, buf);
      std::sprintf(buf, "Yaw= %.2f ; ", fdm.vEulerAngles.z);
      std::strcat(s, buf);
      std::sprintf(buf, "Alt= %.0f ; ", fdm.vPosition.z);
      std::strcat(s, buf);
      std::sprintf(buf, "T= %.0f ; ", fdm.ThrustForce);
      std::strcat(s, buf);
      std::sprintf(buf, "S= %.0f ", fdm.fSpeed/1.688); // divide by 1.688 to convert ft/s to knots
      std::strcat(s, buf);
      if (fdm.Flaps)
         std::strcat(s, "; Flaps");

      if (fdm.Stalling) {
         std::strcat(s, "; Stall!");
         Beep(10000, 250);
      }

      SetWindowText(hTheMainWindow, s);
   } else {
      FrameCounter++;
   }
}

BOOL IsKeyDown(short KeyCode)
{
   SHORT retval{GetAsyncKeyState(KeyCode)};

   if (HIBYTE(retval))
      return TRUE;

   return FALSE;
}
