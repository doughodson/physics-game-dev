
#ifndef __mfc_utils_HPP__
#define __mfc_utils_HPP__

#include <windows.h>
#include <wingdi.h> 

void DrawLineToDC(HDC hdc, int h1, int v1, int h2, int v2, int thk, COLORREF clr);
void DrawRectangleToDC(HDC hdc, RECT* r, int thk, COLORREF borderCLR, COLORREF fillCLR);
void DrawEllipseToDC(HDC hdc, RECT* r, int thk, COLORREF clr);
void DrawStringToDC(HDC hdc, int x, int y, LPCSTR lpszString, int size, int ptsz);
BOOL IsKeyDown(short KeyCode);

#endif

