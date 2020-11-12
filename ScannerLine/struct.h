#pragma once
#include "Point.h"

struct result {
	// 画图时用，存储返回值
	Point pointList[100];
	int pointNumber;
	Point linePoint1[100];
	Point linePoint2[100];
	int lineNumber;
};