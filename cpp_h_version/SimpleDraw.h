// Simple drawing functions for educational purposes (h+cpp version)
// Assembled and coded by FST
#pragma once

#include <windows.h>
#include <iostream>
#include <string.h>

void usePen(int style = PS_SOLID, int width = 1, COLORREF color = RGB(0, 0, 0));
void useBrush(int style = 0, COLORREF color = RGB(255, 255, 255));
static wchar_t* charToWChar(const char* text, size_t *convertedChars);
void _STARTPAINT();
void _ENDPAINT();
void drawLine(int x1, int y1, int x2, int y2);
void drawText(int x, int y, char *text);
void drawRectangle(int x1, int y1, int x2, int y2);
void drawSquare(int x, int y, int a);
void drawEllipse(int x, int y, int rx, int ry);
void drawCircle(int x, int y, int r);
void drawArc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void drawPolygon(int points[][2], int n);
void drawPolyline(int points[][2], int n);
void setWindowSize(int w, int h);
struct thread_data
{
	int m_id;
	thread_data(int id) : m_id(id) {}
};
long __stdcall WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp );
int getMouseX();
int getMouseY();
int getMouseButton();
int getKey();
DWORD WINAPI openWindow(LPVOID lpParameter);
void initialize();
