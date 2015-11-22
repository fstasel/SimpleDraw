// SimpleDraw test program
// By FST

// All you need is to include:
#include "SimpleDraw.h"

void main()
{
	// Adjust window size
	setWindowSize(400, 400);

	// Line (x1,y1,x2,y2)
	drawLine(150, 200, 250, 100);
	// Polygon (array of pointX,Y, arraySize)
	int p[][2] = {{10,10},{90,10},{90,90},{10,10}};
	drawPolygon(p, 4);

	// Use brush
	// style : 0 = NO FILL, 1 = FILL, 2..7 = PATTERNS
	// RGB color
	useBrush(2, RGB(0, 0, 255));

	// Rectangle (x1,y1,x2,y2)
	drawRectangle(50, 100, 100, 250);
	// Square (xCenter,yCenter,side)
	drawSquare(350, 150, 50);

	// Use pen
	// style : PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, or PS_NULL
	// width
	// RGB color
	usePen(PS_DASH, 1, RGB(255, 0, 0));

	// Use brush with no-fill mode
	useBrush();

	// Ellipse (xCenter,yCenter,xRadius,yRadius)
	drawEllipse(175, 300, 25, 50);
	// Circle (xCenter,yCenter,radius)
	drawCircle(175, 300, 50);
	// Text (x,y,string)
	drawText(170, 100, "Hello!");

	// Wait for mouse click
	while(!getMouseButton());
	while(getMouseButton());

	// Bouncing ball demo
	int x = 200, y = 200;
	int vx = 5, vy = 10;
	// Animate until mouse button is pressed
	while(!getMouseButton())
	{
		// Clear scene
		usePen(PS_SOLID);
		useBrush(1);
		drawRectangle(50, 120, 340, 280);
		// Draw ball
		usePen(PS_NULL);
		useBrush(1, RGB(0, 0, 255));
		drawCircle(x, y, 10);
		// Move ball
		if(x + vx < 60 || x + vx > 330) vx = -vx;
		if(y + vy < 130 || y + vy > 270) vy = -vy;
		x += vx; y += vy;
		// Sleep a little
		Sleep(20);
	}

	// Mouse draw demo
	// Clear scene
	usePen(PS_NULL);
	useBrush(1);
	drawRectangle(0, 0, 400, 400);
	usePen(PS_SOLID, 2);
	int x1, y1, x2, y2;
	int b;
	x1 = getMouseX();
	y1 = getMouseY();
	while((b = getMouseButton()) != 2)
	{
		if(b == 1)
		{
			Sleep(10);
			x2 = getMouseX();
			y2 = getMouseY();
			drawLine(x1, y1, x2, y2);
			x1 = x2; y1 = y2;
		}
		else if(b == 0)
		{
			x1 = getMouseX();
			y1 = getMouseY();
		}
	}
}
