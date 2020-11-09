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
	glutInit(&argc, argv);  // 使用glut库需要进行初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  // 设定窗口显示模式，颜色模型和缓存，这里是RGB颜色模型和单缓存
	glutInitWindowPosition(100, 100);  // 设定窗口的初始位置，屏幕左上角为原点，单位为像素
	glutInitWindowSize(600, 500);  // 设定窗口的大小
	glutCreateWindow("扫描线区域填充算法");  // 创建一个窗口，参数是窗口标题名

	Initial();
	glutMainLoop();  // 使窗口框架运行起来，使显示回调函数开始工作
}

void glut::Initial() {
	result result1;

	Graphic graphic;  // 初始化
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
	glColor3f(1.0, 1.0, 1.0);  // 白色
	glPointSize(10.0);  // 大小
	float x = ((float)point.x) / Width - 0.5;
	float y = ((float)point.y) / Width - 0.5;

	// 绘制
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();

	// 刷新
	glFlush();
}

void glut::DrawLine(Point point1, Point point2, int flag) {
	glColor3f(1.0, 1.0, 1.0);  // 白色
	glLineWidth(10.0);  // 线宽
	float x1 = ((float)point1.x) / Width - 0.5;
	float y1 = ((float)point1.y) / Width - 0.5;
	float x2 = ((float)point2.x) / Width - 0.5;
	if (flag = 1) {  // flag = 1 时画点，点宽设为0.032，对应线宽为正方形
		x2 += 0.032;
	}
	float y2 = ((float)point2.y) / Width - 0.5;

	// 绘制
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();

	// 刷新
	glFlush();
}