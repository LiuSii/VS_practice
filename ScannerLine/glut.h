#pragma once
#include "Point.h"

class glut {
	public:
		glut(int argc, char* argv[]);
		void Initial();
		void DrawPoint(Point point);
		void DrawLine(Point point1, Point point2, int flag);
};