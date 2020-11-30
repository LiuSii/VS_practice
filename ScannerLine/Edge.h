#pragma once
#include "Point.h"
#include <cstddef>

class Edge {
	public:
		float yMax;
		float xDown;  // 一边两个顶点中最下面的x
		float dx;   // (dx)/(dy)
		Edge* next;

		// 专门处理水平线的几个属性
		float xMin;
		float xMax;

	public:
		// 分别求取边节点的值
		void forYMax(Point point1, Point point2);
		void forXDown(Point point1, Point point2);
		void forDx(Point point1, Point point2);

		// 求取最小值，用于排序
		int forYMin(Point point1, Point point2);
};

