#include <GL/glut.h>
#include <math.h>
#include<iostream>

const GLfloat factor = 0.1f;
GLfloat num = 0.0f;
GLfloat block_x = -0.01f;
GLfloat block_y = -0.8f;
GLfloat high = 1.0f;
GLfloat width = 2.0f;
GLfloat block_x1 = -0.91f;
GLfloat block_y1 = -0.02f;
void myDisplay(void) {
	GLfloat x;
	//set the backgroud color
	glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//set the point we look it
	glMatrixMode(GL_MODELVIEW);
	//replaces the current matrix with the identity matrix
	glLoadIdentity();
	gluLookAt(0, -0.5, 0.4, 0, 0, 0, 0, 0, 0.5);


	glBegin(GL_LINES);
	//set the color of the line
	glColor3f(0.5f, 1.0f, 1.0f);
	//draw the line
	for (float i = 0.0f; i < 360.0; i += 3.0) {
		for (x = 0; x < 1.0f / factor; x += 0.01f) {
			glVertex3f(x * factor * cos(i), high * (1 - x * factor) * cos(width * x - num) * factor, x * factor * sin(i));
		}
	}
	glEnd();


	/*以下是关于垂直调节杆的设置*/
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.7f, 0.7f);
	glVertex2f(-0.898, 0.5);
	glVertex2f(-0.898, -0.5);
	glVertex2f(-0.883, -0.5);
	glVertex2f(-0.883, 0.5);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.5f, 0.6f);
	glVertex2f(block_x1, block_y1);
	glVertex2f(block_x1, (block_y1 - 0.05));
	glVertex2f(block_x1 + 0.04, block_y1 - 0.05);
	glVertex2f(block_x1 + 0.04, block_y1);
	glEnd();



	/*以下是关于水平的横杆的设置*/
	glBegin(GL_QUADS);
	//glColor3f(0.5f, 1.0f, 1.0f);
	glColor3f(0.3f, 0.7f, 0.7f);
	glVertex2f(-0.5, -0.86);
	glVertex2f(-0.5, -0.9);
	glVertex2f(0.5, -0.9);
	glVertex2f(0.5, -0.86);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.5f, 0.6f);
	glVertex2f(block_x, block_y);
	glVertex2f(block_x, (block_y - 0.14));
	glVertex2f(block_x + 0.02, block_y - 0.14);
	glVertex2f(block_x + 0.02, block_y);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void spinCube() {
	num = num + 0.1;
	glutPostRedisplay();
}

void myReshape(GLsizei w, GLsizei h) {
	//为了调节杆的正常使用，直接固定窗口大小
	glutReshapeWindow(1200, 700);
}


void processMouse(int button, int state, int x, int y) {
	//处理鼠标点击
	if (state == GLUT_DOWN) {
		if (x > 300 && x < 900 && y >= 530 && y < 550) {
			block_x = (x + 0.0f - 300.0f) / 600.0f + (-0.5f);
			width = 4 * (1 - (x + 0.0f - 300.0f) / 600.0f);
		}

		if (x > 56 && x < 72 && y >= 255 && y < 456) {
			block_y1 = 0.5f - (y + 0.0f - 249.0f) / 208.0f;
			high = 2 * (1 - (y + 0.0f - 249.0f) / 208.0f);
		}
	}
}


void processMouseActiveMotion(int x, int y) {
	//处理鼠标拖动
	if (x > 300 && x < 900 && y >= 530 && y < 550) {
		block_x = (x + 0.0f - 300.0f) / 600.0f + (-0.5f);
		width = 4 * (1 - (x + 0.0f - 300.0f) / 600.0f);
	}
	if (x > 56 && x < 72 && y >= 255 && y < 456) {
		block_y1 = 0.5f - (y + 0.0f - 249.0f) / 208.0f;
		high = 2 * (1 - (y + 0.0f - 249.0f) / 208.0f);
	}

}

int main(int argc, char* argv[]) {
	// init
	glutInit(&argc, argv);
	//set mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//set the position
	glutInitWindowPosition(100, 100);
	//set the width and weigth
	glutInitWindowSize(1200, 700);
	glutCreateWindow("很荡漾的水波");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(&myDisplay);
	//to set the action
	glutIdleFunc(spinCube);
	//设置鼠标事件
	//glutMouseFunc(processMouse);
	//glutMotionFunc(processMouseActiveMotion);
	//loop
	glutMainLoop();
	return 0;
}