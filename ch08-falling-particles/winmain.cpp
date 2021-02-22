
#include <windows.h>
#include <windef.h>
#include <commctrl.h>
#include <commdlg.h>
#include <wingdi.h> 

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <math.h>

#include "physics.hpp"
#include "mfc_utils.hpp"

#include "resource.h"

#include "particle.hpp"

#include "winmain.hpp"

#define APPNAME "Physics for Game Developers Chapter 8 Example"

LRESULT CALLBACK DemoDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Window related global variables
HINSTANCE hinst; 
HWND hMainWindow;
RECT MainWindowRect;
HDC BackBufferDC;
HBITMAP hBackBuffer;
LPBITMAPINFO lpBackBufferBitmapInfo;
bool Initialized{};
int nShowCmd{};

bool ShowTrails{};
bool ShowVectors{};

int TargetX{};
int TargetY{};

bool WideView{};
bool LimitedView{};
bool NarrowView{};
bool Chase{};

bool bDoSim{true};

void DrawLine(HDC hdc, int h1, int v1, int h2, int v2, int thk, COLORREF clr);
void DrawRectangle(HDC hdc, RECT *r, int thk, COLORREF clr);
void DrawString(HDC hdc, int x, int y, LPCSTR lpszString, int size, int ptsz);

void UpdateSimulation();
bool Initialize();

//----------------------------------------------------------------------------------------------------
// this is the applications "main" function. Note that I'm not using a message loop here
// since there is no main window. All I do is display a dialog box immediately upon startup
// and let the dialog handler take care of the messages.
//----------------------------------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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

	hAccelTable = LoadAccelerators (hInstance, APPNAME);

	// Main message loop:
	while (1) {		

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}
		
		if(Initialized && bDoSim)
			UpdateSimulation();

	}

	return (msg.wParam);

	lpCmdLine; // This will prevent 'unused formal parameter' warnings
}


BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;
    HWND      hwnd;

    hwnd = FindWindow (APPNAME, NULL);
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
        wc.hIcon         = NULL;//LoadIcon (hInstance, MAKEINTRESOURCE(IDI_MAINICON));
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);//NULL
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//(HBRUSH)(COLOR_WINDOW+1);

		wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
		
		wc.lpszClassName = APPNAME;
        
		return RegisterClass(&wc);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{			
	hinst = hInstance;
	nShowCmd = nCmdShow;	

	MainWindowRect.left = 0;
	MainWindowRect.top = 0;
	MainWindowRect.right = _WINWIDTH;
	MainWindowRect.bottom = _WINHEIGHT;
 
	hMainWindow = CreateWindow(	APPNAME, 
								APPNAME,
								WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
								0, 0, _WINWIDTH, _WINHEIGHT,
								NULL, NULL, hinst, NULL);
			
	// create back buffer
	CreateBackBuffer();

	ShowWindow(hMainWindow, nCmdShow);
    UpdateWindow(hMainWindow);

	Initialized = Initialize();

	return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;   		
	BOOL validmenu = FALSE;	
	int selection =0;
	PAINTSTRUCT ps;
	HDC pDC;
	int w, h;
	UINT state;

	switch (message) {

		case WM_CREATE:
			ShowTrails = false;
			ShowVectors = false;
			WideView = false;
			LimitedView = false;
			NarrowView = false;
			Chase = false;			
			break;

		case WM_ACTIVATE:
			state = ShowTrails ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_SHOWTRAILS, state);
			
			state = ShowVectors ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_SHOWVECTORS, state);

			state = WideView ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_WIDEFIELDOFVIEW, state);

			state = LimitedView ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_LIMITEDFIELDOFVIEW, state);
			
			state = NarrowView ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_NARROWFIELDOFVIEW, state);
			
			state = Chase ? MF_CHECKED:MF_UNCHECKED;
			CheckMenuItem(GetMenu(hMainWindow), ID_OPTIONS_CHASEMOUSE, state);
			
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			
			switch(wmId) {

				case ID_CLOSEMENU:
					DeleteBackBuffer();
					PostQuitMessage(0);
					break;
			}
			break;

		case	WM_MOUSEMOVE:
			TargetX = LOWORD(lParam);
			TargetY = HIWORD(lParam); 
			break;


		case WM_DESTROY:
			DeleteBackBuffer();
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			bDoSim = !bDoSim;

			break;

		case WM_PAINT:			
				pDC = BeginPaint(hMainWindow, (LPPAINTSTRUCT) &ps);

				w = MainWindowRect.right - MainWindowRect.left;
				h = MainWindowRect.bottom - MainWindowRect.top;
				BitBlt(pDC, 0, 0, w, h, BackBufferDC, 0, 0, SRCCOPY);

				EndPaint(hMainWindow, (LPPAINTSTRUCT) &ps);				
				return (0);
			break;
        
		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

void CopyBackBufferToWindow()
{
    HDC dc{GetDC(hMainWindow)};
    const int w{MainWindowRect.right - MainWindowRect.left};
    const int h{MainWindowRect.bottom - MainWindowRect.top};
    BitBlt(dc, 0, 0, w, h, BackBufferDC, 0, 0, SRCCOPY);
    DeleteDC(dc);
}

void ClearBackBuffer()
{
    DrawRectangle(&MainWindowRect, 1, RGB(0, 0, 0), RGB(255, 255, 255));
}

void CreateBackBuffer()
{
    HDC hdc{GetDC(hMainWindow)};

    BackBufferDC = CreateCompatibleDC(hdc);

    lpBackBufferBitmapInfo = (LPBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER));

    lpBackBufferBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    lpBackBufferBitmapInfo->bmiHeader.biWidth = MainWindowRect.right - MainWindowRect.left;
    lpBackBufferBitmapInfo->bmiHeader.biHeight = MainWindowRect.bottom - MainWindowRect.top;
    lpBackBufferBitmapInfo->bmiHeader.biPlanes = 1;
    lpBackBufferBitmapInfo->bmiHeader.biBitCount = 24;
    lpBackBufferBitmapInfo->bmiHeader.biCompression = BI_RGB;
    lpBackBufferBitmapInfo->bmiHeader.biSizeImage = 0;
    lpBackBufferBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
    lpBackBufferBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
    lpBackBufferBitmapInfo->bmiHeader.biClrUsed = 0;
    lpBackBufferBitmapInfo->bmiHeader.biClrImportant = 0;

    BYTE* lpbits{};
    hBackBuffer = CreateDIBSection(BackBufferDC, lpBackBufferBitmapInfo, DIB_RGB_COLORS, (void**)&lpbits, NULL, 0);

    SelectObject(BackBufferDC, (HBITMAP)hBackBuffer);

    DrawRectangleToDC(BackBufferDC, &MainWindowRect, 4, RGB(0, 0, 0), RGB(255, 255, 255));
}

void DeleteBackBuffer()
{
    DeleteDC(BackBufferDC);
    DeleteObject(hBackBuffer);
    free(lpBackBufferBitmapInfo);
}

//----------------------------------------------------------------------------------------------------
// these function draw to the back buffer
//----------------------------------------------------------------------------------------------------
void DrawLine(int x1, int y1, int x2, int y2, int thk, COLORREF clr)
{
    DrawLineToDC(BackBufferDC, x1, y1, x2, y2, thk, clr);
}

void DrawRectangle(RECT* r, int thk, COLORREF borderCLR, COLORREF fillCLR)
{
    DrawRectangleToDC(BackBufferDC, r, thk, borderCLR, fillCLR);
}

void DrawEllipse(RECT* r, int thk, COLORREF clr)
{
    DrawEllipseToDC(BackBufferDC, r, thk, clr);
}
