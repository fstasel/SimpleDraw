#include "Ball.h"

Ball :: Ball()
{
	px = py = pr = 0;
	r = (double)(rand() % 26) + 5;
	setX((double)(rand() % maxX));
	setY((double)(rand() % maxY));
	vx = (double)(rand() % 11) - 5.0;
	vy = (double)(rand() % 11) - 5.0;
	color = RGB(rand() % 256,rand() % 256,rand() % 256);
}

Ball :: Ball(double x, double y, double vx, double vy, double r, COLORREF color)
{
	Ball::x = x;
	Ball::y = y;
	Ball::vx = vx;
	Ball::vy = vy;
	Ball::r = r;
	Ball::color = color;
}

double Ball :: getX() { return x; }

double Ball :: getY() { return y; }

double Ball :: getVx() { return vx; }

double Ball :: getVy() { return vy; }

double Ball :: getR() { return r; }

void Ball :: setX(double x)
{
	if(x < r) x = r;
	else if(x > maxX-r) x = maxX-r;
	Ball::x = x;
}

void Ball :: setY(double y)
{
	if(y < r) y = r;
	else if(y > maxY-r) y = maxX-r;
	Ball::y = y;
}

void Ball :: setVx(double vx)
{
	if(vx < -5.0) vx = -5.0;
	else if(vx > 5.0) vx = 5.0;
	Ball::vx = vx;
}

void Ball :: setVy(double vy)
{
	if(vy < -5.0) vy = -5.0;
	else if(vy > 5.0) vy = 5.0;
	Ball::vy = vy;
}

void Ball :: setR(double r)
{
	if(r < 5.0) r = 5.0;
	else if(r > 25.0) r = 25.0;
	Ball::r = r;
	setX(x);
	setY(y);
}

void Ball :: move()
{
	if(x + vx < r || x + vx > maxX-r) vx = -vx;
	if(y + vy < r || y + vy > maxY-r) vy = -vy;
	x += vx;
	y += vy;
}


void Ball :: draw()
{
	usePen(PS_SOLID, 1, RGB(255,255,255)); // Clear
	useBrush(1, RGB(255,255,255));
	drawCircle((int)px,(int)py,(int)pr);
	usePen(PS_SOLID, 1, RGB(0,0,0));
	useBrush(1, color); 
	drawCircle((int)x,(int)y,(int)r);
	px = x; py = y; pr = r;
}
