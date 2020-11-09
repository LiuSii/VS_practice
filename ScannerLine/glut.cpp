#include "glut.h"
#include <gl/GLUT.H>
#include "Graphic.h"
#include "stdio.h"
#include <iostream>
#include "Point.h"
#include "struct.h"

#define Width 7
#define High 7

glut::glut(int argc, char* argv[]) {
	glutInit(&argc, argv);  // ʹ��glut����Ҫ���г�ʼ��
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  // �趨������ʾģʽ����ɫģ�ͺͻ��棬������RGB��ɫģ�ͺ͵�����
	glutInitWindowPosition(100, 100);  // �趨���ڵĳ�ʼλ�ã���Ļ���Ͻ�Ϊԭ�㣬��λΪ����
	glutInitWindowSize(600, 500);  // �趨���ڵĴ�С
	glutCreateWindow("ɨ������������㷨");  // ����һ�����ڣ������Ǵ��ڱ�����

	Initial();
	glutMainLoop();  // ʹ���ڿ������������ʹ��ʾ�ص�������ʼ����
}

void glut::Initial() {
	result result1;

	Graphic graphic;  // ��ʼ��
	result1 = graphic.Filling();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	for (int i = 0; i < result1.pointNumber; i++) {
		//DrawPoint(result1.pointList[i]);
		DrawLine(result1.pointList[i], result1.pointList[i], 1);
	}
	for (int i = 0; i < result1.lineNumber; i++) {
		DrawLine(result1.linePoint1[i], result1.linePoint2[i], 0);
	}
}

void glut::DrawPoint(Point point) {
	glColor3f(1.0, 1.0, 1.0);  // ��ɫ
	glPointSize(10.0);  // ��С
	float x = ((float)point.x) / Width - 0.5;
	float y = ((float)point.y) / Width - 0.5;

	// ����
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();

	// ˢ��
	glFlush();
}

void glut::DrawLine(Point point1, Point point2, int flag) {
	glColor3f(1.0, 1.0, 1.0);  // ��ɫ
	glLineWidth(10.0);  // �߿�
	float x1 = ((float)point1.x) / Width - 0.5;
	float y1 = ((float)point1.y) / Width - 0.5;
	float x2 = ((float)point2.x) / Width - 0.5;
	if (flag = 1) {  // flag = 1 ʱ���㣬�����Ϊ0.032����Ӧ�߿�Ϊ������
		x2 += 0.032;
	}
	float y2 = ((float)point2.y) / Width - 0.5;

	// ����
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();

	// ˢ��
	glFlush();
}