#pragma once
#include "Point.h"
#include <cstddef>

class Edge {
	public:
		float yMax;
		float xDown;
		float dx;   // (dx)/(dy)
		Edge* next;

	public:
		void forYMax(Point point1, Point point2);
		void forXDown(Point point1, Point point2);
		void forDx(Point point1, Point point2);

		int forYMin(Point point1, Point point2);
};

