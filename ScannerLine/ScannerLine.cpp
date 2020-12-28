// ScannerLine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define MinRange 5

#include <iostream>
#include "Graphic.h"

using namespace std;

#include <GL/glut.h>
#include <thread>
#define MAX_CHAR        128

#include<sstream>

//窗口长宽
int width = 600, height = 400;
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

// 更改颜色变量，初始化为白色
GLfloat pRed = 0.5;
GLfloat pGreen = 0.5;
GLfloat pBlue = 0.5;

// 边界点
Point linePoint1(400, 0);
Point linePoint2(400, 400);

// 三个控制杆
Point sliderBarPointAngle1(460, 50);
Point sliderBarPointAngle2(500, 50);
Point sliderBarPointAngle3(540, 50);
// 三个滑块
Point sliderPointAngle1(458, 150);
Point sliderPointAngle2(498, 150);
Point sliderPointAngle3(538, 150);
// 黑色背景框

int sliderToBlackFlag = 0; // 为1时表示在调颜色，不用画点

// 如果是左键抬起操作标志位，为1则表示为抬起
int leftUpFlag = 0;

// 无效点击，为1则为无效，不用画图
int nullFlag = 0;

void DrawString(const  char* str) {
	static  int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // 如果是第一次调用，执行初始化
						// 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

void DrawNumber(int flag) {
	char* buffer = new char[30];
	// 绘制数字
	switch (flag) {
		case 1:
			glColor3f(1.0f, 0.0f, 0.0f);
			glRasterPos2f(453.0f, 330.0f);
			sprintf_s(buffer, sizeof(buffer), "%.0f", pRed * 255);
			DrawString(buffer);
			break;
		case 2:
			glColor3f(0.0f, 1.0f, 0.0f);
			glRasterPos2f(493.0f, 330.0f);
			sprintf_s(buffer, sizeof(buffer), "%.0f", pGreen * 255);
			DrawString(buffer);
			break;
		case 3:
			glColor3f(0.0f, 0.0f, 1.0f);
			glRasterPos2f(533.0f, 330.0f);
			sprintf_s(buffer, sizeof(buffer), "%.0f", pBlue * 255);
			DrawString(buffer);
			break;
		default:
			break;
	}
}

void DrawBlackBack(int flag) {  // 控制杆背景置黑色
	switch (flag) {
		case 1:
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(sliderBarPointAngle1.x - 12, sliderBarPointAngle1.y - 20);
			glVertex2f(sliderBarPointAngle1.x + 17, sliderBarPointAngle1.y - 20);
			glVertex2f(sliderBarPointAngle1.x + 17, sliderBarPointAngle1.y + 350);
			glVertex2f(sliderBarPointAngle1.x - 12, sliderBarPointAngle1.y + 350);
			glEnd();
			break;
		case 2:
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(sliderBarPointAngle2.x - 12, sliderBarPointAngle2.y - 20);
			glVertex2f(sliderBarPointAngle2.x + 17, sliderBarPointAngle2.y - 20);
			glVertex2f(sliderBarPointAngle2.x + 17, sliderBarPointAngle2.y + 350);
			glVertex2f(sliderBarPointAngle2.x - 12, sliderBarPointAngle2.y + 350);
			glEnd();
			break;
		case 3:
			glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(sliderBarPointAngle3.x - 12, sliderBarPointAngle3.y - 20);
			glVertex2f(sliderBarPointAngle3.x + 17, sliderBarPointAngle3.y - 20);
			glVertex2f(sliderBarPointAngle3.x + 17, sliderBarPointAngle3.y + 350);
			glVertex2f(sliderBarPointAngle3.x - 12, sliderBarPointAngle3.y + 350);
			glEnd();
			break;
		default:
			break;
	}
}


void DrawBar(Point anglePoint1) {
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.5f, 0.6f);
	glVertex2f(anglePoint1.x, anglePoint1.y);
	glVertex2f(anglePoint1.x + 9, anglePoint1.y);
	glVertex2f(anglePoint1.x + 9, anglePoint1.y + 40);
	glVertex2f(anglePoint1.x, anglePoint1.y + 40);
	glEnd();
}

void DrawVerLine(Point anglePoint1) {
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.7f, 0.7f);
	glVertex2f(anglePoint1.x, anglePoint1.y);
	glVertex2f(anglePoint1.x + 5, anglePoint1.y);
	glVertex2f(anglePoint1.x + 5, anglePoint1.y + 240);
	glVertex2f(anglePoint1.x, anglePoint1.y + 240);
	glEnd();
}

void DrawLine(Point point1, Point point2, int flag) {
	glColor3f(pRed, pGreen, pBlue);  // 白色
	glLineWidth(3.0);  // 线宽

	// 绘制
	glBegin(GL_LINES);
	glVertex2f(point1.x, point1.y);
	glVertex2f(point2.x, point2.y);
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
	if ((button == 0) && (state == GLUT_UP)) {
		leftUpFlag = 1;
	}

	//鼠标操作基本结构
	switch (button) {
		case GLUT_LEFT_BUTTON:	//左键操作，也可为数字0
			if (state == GLUT_DOWN)	{//左键按下时
				leftUpFlag = 0;
				if (x >= 460 && x <= 465 && y >= 50 && y <= 290) { // 控制第一个滑块
					nullFlag = 0;
					sliderPointAngle1.y = y - 20;
					pRed = (290 - y) / (240.0);
					sliderToBlackFlag = 1;
				} else if (x >= 500 && x <= 505 && y >= 50 && y <= 290) {  // 控制第二个滑块
					nullFlag = 0;
					sliderPointAngle2.y = y - 20;
					pGreen = (290 - y) / (240.0);
					sliderToBlackFlag = 2;
				} else if (x >= 540 && x <= 545 && y >= 50 && y <= 290) {  // 控制第三个滑块
					nullFlag = 0;
					sliderPointAngle3.y = y - 20;
					pBlue = (290 - y) / (240.0);
					sliderToBlackFlag = 3;
				} else if (x <= 400) {
					nullFlag = 0;
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
				} else {
					nullFlag = 1;
				}
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

	if (button_kind == 0 && leftUpFlag == 0 && nullFlag == 0) {  // 左键点击
		if (sliderToBlackFlag == 0) {
			// 画一个白色的点
			glPointSize(5);
			glBegin(GL_POINTS);
			glColor3f(pRed, pGreen, pBlue);
			glVertex2f(hit_pos_x, hit_pos_y);
			glEnd();
			glFlush();
			// 绘制连线
			if (lastPoint.x != -1 & lastPoint.y != -1) {
				//画一条白色的线
				glLineWidth(5);
				glColor3f(pRed, pGreen, pBlue);
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
		} else if (sliderToBlackFlag == 1) {
			DrawBlackBack(1);
			DrawNumber(1);
			glFlush();
			sliderToBlackFlag = 0;
			button_kind = 10;
		} else if (sliderToBlackFlag == 2) {
			DrawBlackBack(2);
			DrawNumber(2);
			glFlush();
			sliderToBlackFlag = 0;
			button_kind = 10;
		} else if (sliderToBlackFlag == 3) {
			DrawBlackBack(3);
			DrawNumber(3);
			glFlush();
			sliderToBlackFlag = 0;
			button_kind = 10;
		}
	} else if (button_kind == 2) {  // 右键点击
		// 清除屏幕
		firstPoint.x = -1;
		firstPoint.y = -1;
		lastPoint.x = -1;
		lastPoint.y = -1;
		fillFlag = 0;
		drawLineFlag = 0;
		pointNumber = 0;  // 点个数
		
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
	
	// 绘制边界与框
	DrawLine(linePoint1, linePoint2, 0);
	DrawVerLine(sliderBarPointAngle1);
	DrawVerLine(sliderBarPointAngle2);
	DrawVerLine(sliderBarPointAngle3);
	DrawBar(sliderPointAngle1);
	DrawBar(sliderPointAngle2);
	DrawBar(sliderPointAngle3);
	DrawNumber(1);
	DrawNumber(2);
	DrawNumber(3);

	glFlush();

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
