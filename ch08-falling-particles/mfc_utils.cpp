
#include "mfc_utils.hpp"

#include <windows.h>
#include <windef.h>
#include <commctrl.h>
#include <commdlg.h>
#include <wingdi.h> 

//----------------------------------------------------------------------------------------------------
// This function simply draws a solid line to the given device context, given the line
// start and end point, its thickness and its color.
//----------------------------------------------------------------------------------------------------
void DrawLineToDC(HDC hdc, int h1, int v1, int h2, int v2, int thk, COLORREF clr)
{
	HBRUSH CurrentBrush;
	HBRUSH OldBrush;
	HPEN CurrentPen;
	HPEN OldPen;
	COLORREF	FColor = clr;
	COLORREF	BColor = RGB(0, 0, 0);

	CurrentBrush = CreateSolidBrush(FColor);
	OldBrush = (HBRUSH)SelectObject(hdc, CurrentBrush);
	CurrentPen = CreatePen(PS_SOLID, thk, FColor);
	OldPen = (HPEN)SelectObject(hdc, CurrentPen);

	MoveToEx(hdc, h1, v1, NULL);
	LineTo(hdc, h2, v2);

	SelectObject(hdc, OldBrush);
	SelectObject(hdc, OldPen);
	DeleteObject(CurrentBrush);
	DeleteObject(CurrentPen);
}

//----------------------------------------------------------------------------------------------------
// This function simply draws a filled rectangle to the given device context, given the
// rectangle dimensions, its border thickness and its border color (the rectangle is filled
// in black).
//----------------------------------------------------------------------------------------------------
void DrawRectangleToDC(HDC hdc, RECT* r, int thk, COLORREF borderCLR, COLORREF fillCLR)
{
	HBRUSH		CurrentBrush;
	HBRUSH		OldBrush;
	HPEN		CurrentPen;
	HPEN		OldPen;
	COLORREF	FColor = borderCLR;
	COLORREF	BColor = fillCLR;

	CurrentBrush = CreateSolidBrush(BColor);
	OldBrush = (HBRUSH)SelectObject(hdc, CurrentBrush);
	CurrentPen = CreatePen(PS_SOLID, thk, FColor);
	OldPen = (HPEN)SelectObject(hdc, CurrentPen);

	Rectangle(hdc, r->left, r->top, r->right, r->bottom);

	SelectObject(hdc, OldBrush);
	SelectObject(hdc, OldPen);
	DeleteObject(CurrentBrush);
	DeleteObject(CurrentPen);
}

//----------------------------------------------------------------------------------------------------
// This function simply draws a filled rectangle to the given device context, given the
// rectangle dimensions, its border thickness and its border color (the rectangle is filled
// in black).
//----------------------------------------------------------------------------------------------------
void DrawEllipseToDC(HDC hdc, RECT* r, int thk, COLORREF clr)
{
	HBRUSH		CurrentBrush;
	HBRUSH		OldBrush;
	HPEN		CurrentPen;
	HPEN		OldPen;
	COLORREF	FColor = clr;
	COLORREF	BColor = RGB(0, 0, 0);

	CurrentBrush = CreateSolidBrush(BColor);
	OldBrush = (HBRUSH)SelectObject(hdc, CurrentBrush);
	CurrentPen = CreatePen(PS_SOLID, thk, FColor);
	OldPen = (HPEN)SelectObject(hdc, CurrentPen);

	Ellipse(hdc, r->left, r->top, r->right, r->bottom);

	SelectObject(hdc, OldBrush);
	SelectObject(hdc, OldPen);
	DeleteObject(CurrentBrush);
	DeleteObject(CurrentPen);
}


//----------------------------------------------------------------------------------------------------
// This function simply draws text to the given device context, given the text string
// and the x,y coordinates of its lower left corner, the number of characters in the string,
// and the desired point size.
//----------------------------------------------------------------------------------------------------
void DrawStringToDC(HDC hdc, int x, int y, LPCSTR lpszString, int size, int ptsz)
{
	COLORREF	FColor = RGB(255, 255, 255);
	COLORREF	BColor = RGB(0, 0, 0);
	HFONT		hFont, hOldFont;

	SetTextColor(hdc, FColor);
	SetBkColor(hdc, BColor);
	SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_BOTTOM | TA_LEFT);

	hFont = CreateFont(-ptsz, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, "MS Serif");
	hOldFont = (HFONT)SelectObject(hdc, hFont);

	TextOut(hdc, x, y, lpszString, size);

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
}

BOOL IsKeyDown(short KeyCode)
{

	SHORT	retval;

	retval = GetAsyncKeyState(KeyCode);

	if (HIBYTE(retval))
		return TRUE;

	return FALSE;
}
