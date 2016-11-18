#include "Ball.h"
#include <time.h>

void main()
{
	// Adjust window size
	setWindowSize(400, 400);

	// Ball count
	const int num = 10;
	srand((unsigned int)time(0));

	// Create Ball array
	Ball* b = new Ball[num];

	while(getMouseButton() == 0) // Loop until mouse click
	{
		for(int i = 0; i < num; i++)
		{
			b[i].draw();
			b[i].move();
		}
		drawText(150,20,"Click to exit");
		// Wait a while
		Sleep(20);
	}

	delete [] b;
}
