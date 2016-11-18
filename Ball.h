#pragma once

#include "SimpleDraw.h"

class Ball
{
private:
	double px,py,pr;
	double x,y;
	double vx,vy;
	double r;
	COLORREF color;
	static const int maxX = 400;
	static const int maxY = 400;
public:
	Ball();
	Ball(double, double, double, double, double, COLORREF);
	double getX();
	double getY();
	double getVx();
	double getVy();
	double getR();
	void setX(double);
	void setY(double);
	void setVx(double);
	void setVy(double);
	void setR(double);
	void move();
	void draw();
};
