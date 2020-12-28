// ScannerLine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define MinRange 5

#include <iostream>
#include "Graphic.h"

using namespace std;

#include <GL/glut.h>
#include <thread>

//窗口长宽
int width = 400, height = 400;
//鼠标点击位置
int hit_pos_x, hit_pos_y;
//鼠标操作种类
int button_kind = -1;
// 记录第一个点的值
Point firstPoint(-1, -1);
// 记录上一个点的值
Point lastPoint(-1, -1);
// 需要绘制连线标志位，为0则不需要绘制
int drawLineFlag = 0;
Point pointArray[100];
int pointNumber = 0;  // 点个数

int fillFlag = 0;  // 填充标志，为1时表示可填充
result result1;  // 填充点结构体

void DrawLine(Point point1, Point point2, int flag) {
	glColor3f(1.0f, 1.0f, 1.0f);  // 白色
	glLineWidth(3.0);  // 线宽

	// 绘制
	glBegin(GL_LINES);
	glVertex2f(point1.x, point1.y);
	if (flag == 0) {  // flag为1时画顶点
		glVertex2f(point2.x, point2.y);
	} else {
		glVertex2f(point2.x, point2.y);
	}
	glEnd();

}

void fillFunc() {
	Graphic graphic(pointArray, pointNumber);  // 初始化
	result1 = graphic.Filling();
	fillFlag = 1;
}

void mouse_hit(int button, int state, int x, int y) {
	//鼠标操作种类赋值
	button_kind = button;

	//鼠标操作基本结构
	switch (button) {
		case GLUT_LEFT_BUTTON:	//左键操作，也可为数字0
			if (state == GLUT_DOWN)	{//左键按下时
				if (firstPoint.x == -1 || firstPoint.y == -1) {  // 判断是不是第一个点
					// 如果是第一个点则保存
					firstPoint.x = x;
					firstPoint.y = y;
					pointArray[pointNumber].x = x;
					pointArray[pointNumber].y = y;
					pointNumber++;
				} else {  // 如果不是第一个点，存入数组
					// 判断是否闭环
					if (((x <= firstPoint.x + MinRange) && (x >= firstPoint.x - MinRange)) && ((y <= firstPoint.y + MinRange) && (y >= firstPoint.y - MinRange))) {
						std::thread fillThread(fillFunc);  // 闭环则调用子线程进行填充
						fillThread.detach();
					} else {
						pointArray[pointNumber].x = x;
						pointArray[pointNumber].y = y;
						pointNumber++;
					}
				}
				//记录按键位置
				hit_pos_x = x;
				hit_pos_y = y;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN) {
				cout << "------------------------------------------------------------" << endl;
			}
		default:
			break;
	}
}

void display() {
	// 重新设置OpenGL窗口：原点位置为左上角，x轴从左到右，y轴从上到下，坐标值与像素坐标值相同
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);

	if (button_kind == 0)	{// 左键点击
		// 画一个白色的点
		glPointSize(10);
		glBegin(GL_POINTS);
			glColor3f(1.0f, 1.0f, 1.0f);
		    glVertex2f(hit_pos_x, hit_pos_y);
		glEnd();
		glFlush();
		// 绘制连线
		if (lastPoint.x != -1 & lastPoint.y != -1) {
			//画一条白色的线
			glLineWidth(5);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_LINES);
				glVertex2f((int)lastPoint.x, (int)lastPoint.y);
				glVertex2f(hit_pos_x, hit_pos_y);
			glEnd();
			//glFlush();
		} else {
			drawLineFlag = 1;
		}
		// 将这个点置为上一个点
		lastPoint.x = hit_pos_x;
		lastPoint.y = hit_pos_y;
	} else if (button_kind == 2) {  // 右键点击
		// 清除屏幕
		firstPoint.x = -1;
		firstPoint.y = -1;
		lastPoint.x = -1;
		lastPoint.y = -1;
		fillFlag = 0;
		drawLineFlag = 0;
		pointArray[100] = {};
		pointNumber = 0;  // 点个数
		result1;  // 填充点结构体
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	} else {
		glFlush();
	}

	if (fillFlag == 1) {
		for (int i = 0; i < result1.pointNumber; i++) {
			//DrawPoint(result1.pointList[i]);
			DrawLine(result1.pointList[i], result1.pointList[i], 1);  // 画点函数和画线函数有偏差，统一用画线
		}
		for (int i = 0; i < result1.lineNumber; i++) {
			DrawLine(result1.linePoint1[i], result1.linePoint2[i], 0);
		}
		fillFlag = 0;

		// 刷新
		glFlush();
	}
	//glFlush();

	//每次更新显示
	glutPostRedisplay();
}

int main(int argc, char* argv[]){

	//初始化GL
	glutInit(&argc, argv);
	//设置显示参数(单缓存，RGB格式)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//设置窗口尺寸：width*height
	glutInitWindowSize(width, height);
	//设置窗口位置：在屏幕左上角像素值(100,100)处
	glutInitWindowPosition(100, 100);
	//设置窗口名称
	glutCreateWindow("扫描线算法简单实现");
	//显示函数，display事件需要自行编写
	glutDisplayFunc(display);
	//鼠标点击函数，mouse_hit事件需要自行编写
	glutMouseFunc(mouse_hit);

	//重复循环GLUT事件
	glutMainLoop();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
