#pragma once
#include "Point.h"
#include "stdio.h"
#include "string.h"
#include "Edge.h"
#include "glut.h"
#include "struct.h"

#define scannerNumber 400// ɨ��������

class Graphic {
	public:
		Edge edgeStruct[scannerNumber] = { 0, 0, 0, NULL };  // �ṹ

	public:
		Graphic(Point array[], int number);  // ���캯�������ɳ�ʼ��ET��
		result Filling();  // ��亯��
};