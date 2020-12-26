#pragma once
#include "Point.h"

struct result {
	// 画图时用，存储返回值
	Point pointList[10000];
	int pointNumber;
	Point linePoint1[10000];
	Point linePoint2[10000];
	int lineNumber;
};