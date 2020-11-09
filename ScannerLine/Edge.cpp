#include "Edge.h"
#include "climits"

void Edge :: forYMax(Point point1, Point point2) {
	if (point1.y > point2.y) {
		this->yMax = point1.y;
	} else {
		this->yMax = point2.y;
	}
}

void Edge :: forXDown(Point point1, Point point2) {
	if (point1.y > point2.y) {
		this->xDown = point2.x;
	} else {
		this->xDown = point1.x;
	}
}

void Edge :: forDx(Point point1, Point point2) {
	if (point1.y == point2.y) {  // 平行线情况
		this->dx = INT_MAX;
	} else {
		this->dx = (float)(point1.x - point2.x) / (float)(point1.y - point2.y);
	}
}

int Edge :: forYMin(Point point1, Point point2) {
	if (point1.y < point2.y) {
		return point1.y;
	} else {
		return point2.y;
	}
}