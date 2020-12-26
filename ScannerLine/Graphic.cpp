#include "Graphic.h"
#include "Edge.h"
#include "iostream"
#include "stdio.h"
#include "string.h"
#include "gl\glut.h"
#include "glut.h"
#include "struct.h"
#include "windows.h"

#define scannerNumber 9// 扫描线数量

Graphic :: Graphic() {
	char lineChar[100] = { '/0' };
	Edge* p;

	// 获取图形
	


	// 读入图形中的点
	FILE *fp;
	fopen_s(&fp, "point4.txt", "r");  // 读入的文件为多个边，一条边一行
	while (!feof(fp)) {
		memset(lineChar, 0, sizeof(lineChar));
		fgets(lineChar, sizeof(lineChar) - 1, fp);  // 删除最后的换行符

		Point linkPoint1((int)lineChar[0] - 48, (int)lineChar[2] - 48);  // 字符串转整形
		Point linkPoint2((int)lineChar[4] - 48, (int)lineChar[6] - 48);

		// 扫描线两点转线段，建立边表
		for (int i = 0; i <= scannerNumber; i++) {
			if ((i == linkPoint1.y) || (i == linkPoint2.y)) {
				Edge* linkEdge = (Edge*)malloc(sizeof(Edge));
				linkEdge->next = NULL;

				linkEdge->forYMax(linkPoint1, linkPoint2);  // 求yMax
				linkEdge->forXDown(linkPoint1, linkPoint2);  // 求xDown
				linkEdge->forDx(linkPoint1, linkPoint2);  // 求Dx

				// 如果是水平线则补充最大最小x值
				if (linkEdge->dx == INT_MAX) {
					if (linkPoint1.x > linkPoint2.x) {
						linkEdge->xMin = linkPoint2.x;
						linkEdge->xMax = linkPoint1.x;
					} else {
						linkEdge->xMin = linkPoint1.x;
						linkEdge->xMax = linkPoint2.x;
					}
				}
				
				// 将边结点挂载在扫描线上
				if (i == linkEdge->forYMin(linkPoint1, linkPoint2)) {
					p = &this->edgeStruct[i];
					while (p->next != NULL) {
						p = p->next;
					}
					p->next = linkEdge;
				}
				break;
			}
		}
	}
	fclose(fp);
}

result Graphic::Filling() {
	// 填充函数，用于ET表演化
	Edge* fontEdge = (Edge*)malloc(sizeof(Edge));  // 头结点
	fontEdge->next = NULL;
	Edge* p;
	Edge* q;
	Edge* r;

	result result2;
	result2.pointNumber = 0;
	result2.lineNumber = 0;

	float fillX1, fillX2;  // 填充的起点和终点
	int fillXLock = 0;  // 填充锁
	int fillEnable = 0;

	for (int i = 0; i <= scannerNumber; i++) {
		// 已有结点删除
		p = fontEdge;
		while (p->next != NULL) {
			if (p->next->yMax == i) {
				result2.pointList[result2.pointNumber].x = p->next->xDown;
				result2.pointList[result2.pointNumber].y = i;
				result2.pointNumber++;

				p->next = p->next->next;
			} else {
				p = p->next;
			}
		}

		if (i == scannerNumber && fontEdge->next == NULL) {  // 结束程序
			break;
		}

		// 新结点挂载
		p = fontEdge;
		q = &this->edgeStruct[i];
		while (q->next != NULL) {
			// 从小到大排列结点
			p = fontEdge;
			while (p->next != NULL && q->next->xDown > p->next->xDown) {  
				p = p->next;
			}
			r = q->next;
			q->next = q->next->next;
			r->next = p->next;
			p->next = r;
		}

		// 输出当前AET
		p = fontEdge;
		std::cout << i <<":  ";
		while (p->next != NULL) {
			std::cout << "|" << p->next->yMax << "|" << p->next->xDown << "|" << p->next->dx << "|";
			if (p->next->next != NULL) {
				std::cout << "--------->";
			}
			p = p->next;
		}
		std::cout << "\n";

		// 填充
		p = fontEdge;
		while (p->next != NULL) {
			if (p->next->dx == INT_MAX) {  // 水平线去除、填充
				result2.linePoint1[result2.lineNumber].x = p->next->xMin;
				result2.linePoint1[result2.lineNumber].y = i;
				result2.linePoint2[result2.lineNumber].x = p->next->xMax;
				result2.linePoint2[result2.lineNumber].y = i;
				result2.lineNumber++;

				p->next = p->next->next;
				continue;
			}
			if (fillXLock == 0) {  // 以Lock标志是线段顶点还是末端，进行记录
				fillX1 = p->next->xDown;
				fillXLock = 1;
			} else {
				fillX2 = p->next->xDown;
				fillXLock = 0;
				fillEnable = 1;
			}
			if (fillEnable == 1) {  // 填充可用时进行填充
				result2.linePoint1[result2.lineNumber].x = fillX1;
				result2.linePoint1[result2.lineNumber].y = i;
				result2.linePoint2[result2.lineNumber].x = fillX2;
				result2.linePoint2[result2.lineNumber].y = i;
				result2.lineNumber++;

				fillEnable = 0;
			}
			p = p->next;
		}

		// 更新AET
		p = fontEdge;
		while (p->next != NULL) {
			p->next->xDown = p->next->xDown + p->next->dx;  // x增长

			p = p->next;
		}
	}
	return result2;
}