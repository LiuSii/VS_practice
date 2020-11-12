#pragma once
#include "Point.h"
#include <cstddef>

class Edge {
	public:
		float yMax;
		float xDown;  // һ�������������������x
		float dx;   // (dx)/(dy)
		Edge* next;

	public:
		// �ֱ���ȡ�߽ڵ��ֵ
		void forYMax(Point point1, Point point2);
		void forXDown(Point point1, Point point2);
		void forDx(Point point1, Point point2);

		// ��ȡ��Сֵ����������
		int forYMin(Point point1, Point point2);
};

