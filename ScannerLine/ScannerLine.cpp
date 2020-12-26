// ScannerLine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Graphic.h"

using namespace std;

#include <GL/glut.h>

//窗口长宽
int width = 400, height = 400;
//鼠标点击位置
int hit_pos_x, hit_pos_y;
//Point curPoint(0, 0);
//鼠标操作种类
int button_kind = -1;

// 记录第一个点的值
Point firstPoint(-1, -1);
// 记录上一个点的值
Point lastPoint(-1, -1);

// 需要绘制连线标志位，为0则不需要绘制
int drawLineFlag = 0;

void mouse_hit(int button, int state, int x, int y) {
	//鼠标操作种类赋值
	button_kind = button;

	//鼠标操作基本结构
	switch (button) {
		case GLUT_LEFT_BUTTON:	//左键操作，也可为数字0
			if (state == GLUT_DOWN)	{//左键按下时
				if (firstPoint.x == -1) {  // 判断是不是第一个点
					// 如果是第一个点则保存
					firstPoint.x = x;
					firstPoint.y = y;
				} else {  // 如果不是第一个点，将其与上一个点连线，连线加入ET表

				}
				//记录按键位置
				hit_pos_x = x;
				hit_pos_y = y;
				cout << "x:" << x << "," << "y:" << y << endl;
			}
			break;
		default:
			break;
	}
}

void display() {
	// 重新设置OpenGL窗口：原点位置为左上角，x轴从左到右，y轴从上到下，坐标值与像素坐标值相同
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
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
		drawLineFlag = 0;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	} else {
		glFlush();
	}
	//glFlush();

	//每次更新显示
	glutPostRedisplay();
}

int main(int argc, char* argv[]){
	cout << "test" << endl;

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

	//glut glutObj(argc, argv);

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
