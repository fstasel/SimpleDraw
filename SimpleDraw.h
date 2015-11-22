// Simple drawing functions for educational purposes
// Assembled and coded by FST

#include <windows.h>
#include <iostream>
#include <string.h>

volatile int initialized = 0;
volatile int doPaint = 0;
volatile HDC hDC;
volatile HWND window;
PAINTSTRUCT ps;
const size_t newsize = 100;
wchar_t wcstring[newsize];
volatile HPEN pen = NULL;
volatile HBRUSH brush = NULL;
volatile int mouseX = 0, mouseY = 0;
volatile int mouseButton = 0;

void initialize();

void usePen(int style = PS_SOLID, int width = 1, COLORREF color = RGB(0, 0, 0))
{
	// style : PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, or PS_NULL
	if(!initialized) initialize();
	while(!initialized);
	if(pen) DeleteObject(pen);
	pen = CreatePen(style, width, color);
}

void useBrush(int style = 0, COLORREF color = RGB(255, 255, 255))
{
	// style : 0 = NO FILL, 1 = FILL, 2..7 = PATTERNS
	if(!initialized) initialize();
	while(!initialized);
	if(brush) DeleteObject(brush);
	switch(style) {
	case 1:
		brush = CreateSolidBrush(color); break;
	case 2:
		brush = CreateHatchBrush(HS_BDIAGONAL,  color); break;
	case 3:
		brush = CreateHatchBrush(HS_CROSS,  color); break;
	case 4:
		brush = CreateHatchBrush(HS_DIAGCROSS,  color); break;
	case 5:
		brush = CreateHatchBrush(HS_FDIAGONAL,  color); break;
	case 6:
		brush = CreateHatchBrush(HS_HORIZONTAL,  color); break;
	case 7:
		brush = CreateHatchBrush(HS_VERTICAL,  color); break;
	default:
		brush = NULL; break;
	}
}

static wchar_t* charToWChar(const char* text, size_t *convertedChars)
{
	size_t size = strlen(text) + 1;
	mbstowcs_s(convertedChars, wcstring, size, text, _TRUNCATE);
	return wcstring;
}

void _STARTPAINT()
{
	if(!initialized) initialize();
	while(!initialized);
	while(doPaint != 0);
	RedrawWindow(window, NULL, NULL, RDW_INVALIDATE);
	doPaint = 1;
	while(doPaint != 2);
}

void _ENDPAINT()
{
	doPaint = 3;
}

void drawLine(int x1, int y1, int x2, int y2)
{
	_STARTPAINT();
	MoveToEx(hDC, x1, y1, NULL);
	LineTo(hDC, x2, y2);
	_ENDPAINT();
}

void drawText(int x, int y, char *text)
{
	size_t l;
	std::wstring tmp(charToWChar(text, &l));
	LPCWSTR t = tmp.c_str();
	_STARTPAINT();
	TextOut(hDC, x, y, t, l);
	_ENDPAINT();
}

void drawRectangle(int x1, int y1, int x2, int y2)
{
	_STARTPAINT();
	Rectangle(hDC, x1, y1, x2, y2);
	_ENDPAINT();
}

void drawSquare(int x, int y, int a)
{
	_STARTPAINT();
	Rectangle(hDC, x - (a >> 1), y - (a >> 1), x + (a >> 1), y + (a >> 1));
	_ENDPAINT();
}

void drawEllipse(int x, int y, int rx, int ry)
{
	_STARTPAINT();
	Ellipse(hDC, x - rx, y - ry, x + rx, y + ry);
	_ENDPAINT();
}

void drawCircle(int x, int y, int r)
{
	_STARTPAINT();
	Ellipse(hDC, x - r, y - r, x + r, y + r);
	_ENDPAINT();
}

void drawPolygon(int points[][2], int n)
{
	POINT *p = (POINT *) points;
	_STARTPAINT();
	Polygon(hDC, p, n);
	_ENDPAINT();
}

void setWindowSize(int w, int h)
{
	if(!initialized) initialize();
	while(!initialized);
	SetWindowPos(window, NULL, 0, 0, w, h, SWP_NOMOVE);
}

struct thread_data
{
	int m_id;
	thread_data(int id) : m_id(id) {}
};

long __stdcall WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp )
{
	switch(msg)
	{
	case WM_PAINT:

		if(doPaint == 1)
		{
			hDC = BeginPaint(window, &ps);
			SelectObject(hDC, pen);
			if(brush) SelectObject(hDC, brush);
			else SelectObject(hDC, GetStockObject( NULL_BRUSH ));
			doPaint = 2;
			while(doPaint != 3);
			EndPaint(window, &ps);
		}
		doPaint = 0;
		return 0L;
	case WM_DESTROY:
		std::cout << "\nDestroying window\n" ;
		PostQuitMessage(0) ;
		return 0L;
	case WM_LBUTTONDOWN:
		mouseButton = 1;
		return DefWindowProc( window, msg, wp, lp ) ;
	case WM_RBUTTONDOWN:
		mouseButton = 2;
		return DefWindowProc( window, msg, wp, lp ) ;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		mouseButton = 0;
		return DefWindowProc( window, msg, wp, lp ) ;
	case WM_MOUSEMOVE:
		mouseX = LOWORD(lp);
		mouseY = HIWORD(lp);
		return DefWindowProc( window, msg, wp, lp ) ;
	default:
		return DefWindowProc( window, msg, wp, lp ) ;
	}
}

int getMouseX() { return mouseX; }
int getMouseY() { return mouseY; }
int getMouseButton() { return mouseButton; }

DWORD WINAPI openWindow(LPVOID lpParameter)
{
	thread_data *td = (thread_data*)lpParameter;

	std::cout << "Opening window!\n" ;

	WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
		0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
		LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW+1),
		0, L"myclass", LoadIcon(0,IDI_APPLICATION) } ;
	if( RegisterClassEx(&wndclass) )
	{
		window = CreateWindowEx( 0, L"myclass", L"Output window",
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), 0 ) ;
		if(window)
		{
			ShowWindow( window, SW_SHOWDEFAULT ) ;
			initialized = 1;
			MSG msg ;
			while( GetMessage( &msg, 0, 0, 0 ) ) DispatchMessage(&msg);
		}
	}

	return 0;
}

void initialize()
{
	if(!initialized)
	{
		CreateThread(NULL, 0, openWindow, new thread_data(0) , 0, 0);
		while(!initialized);
		if(initialized)
		{
			usePen();
			useBrush();
		}
	}
}
