#include "Graphic.h"
#include "Edge.h"
#include "iostream"
#include "stdio.h"
#include "string.h"
#include "gl\glut.h"
#include "glut.h"
#include "struct.h"

#define scannerNumber 5// ɨ��������

Graphic :: Graphic() {
	char lineChar[100] = { '/0' };
	Edge* p;

	// ����ͼ���еĵ�
	FILE *fp;
	fopen_s(&fp, "point.txt", "r");
	while (!feof(fp)) {
		memset(lineChar, 0, sizeof(lineChar));
		fgets(lineChar, sizeof(lineChar) - 1, fp);  // ɾ�����Ļ��з�

		Point linkPoint1((int)lineChar[0] - 48, (int)lineChar[2] - 48);  // �ַ���ת����
		Point linkPoint2((int)lineChar[4] - 48, (int)lineChar[6] - 48);

		// ɨ��������ת�߶Σ������߱�
		for (int i = 0; i <= scannerNumber; i++) {
			if ((i == linkPoint1.y) || (i == linkPoint2.y)) {
				Edge* linkEdge = (Edge*)malloc(sizeof(Edge));
				linkEdge->next = NULL;

				linkEdge->forYMax(linkPoint1, linkPoint2);  // ��yMax
				linkEdge->forXDown(linkPoint1, linkPoint2);  // ��xDown
				linkEdge->forDx(linkPoint1, linkPoint2);  // ��Dx
				
				// ���߽�������ɨ������
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
	Edge* fontEdge = (Edge*)malloc(sizeof(Edge));  // ͷ���
	fontEdge->next = NULL;
	Edge* p;
	Edge* q;
	Edge* r;

	result result2;
	result2.pointNumber = 0;
	result2.lineNumber = 0;

	float fillX1, fillX2;  // ���������յ�
	int fillXLock = 0;
	int fillEnable = 0;

	for (int i = 0; i <= scannerNumber; i++) {
		// ���н��ɾ��
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

		if (i == scannerNumber && fontEdge->next == NULL) {  // ��������
			break;
		}

		// �½�����
		p = fontEdge;
		q = &this->edgeStruct[i];
		while (q->next != NULL) {
			// ��С�������н��
			p = fontEdge;
			while (p->next != NULL && q->next->xDown > p->next->xDown) {  
				p = p->next;
			}
			r = q->next;
			q->next = q->next->next;
			r->next = p->next;
			p->next = r;
		}

		// ���
		p = fontEdge;
		while (p->next != NULL) {
			if (p->next->dx == INT_MAX) {  // ȥ��ƽ����
				p->next = p->next->next;
				continue;
			}
			if (fillXLock == 0) {
				fillX1 = p->next->xDown;
				fillXLock = 1;
			} else {
				fillX2 = p->next->xDown;
				fillXLock = 0;
				fillEnable = 1;
			}
			if (fillEnable == 1) {  // ������ʱ�������
				result2.linePoint1[result2.lineNumber].x = fillX1;
				result2.linePoint1[result2.lineNumber].y = i;
				result2.linePoint2[result2.lineNumber].x = fillX2;
				result2.linePoint2[result2.lineNumber].y = i;\
				result2.lineNumber++;

				fillEnable = 0;
			}
			p = p->next;
		}

		// ����
		p = fontEdge;
		while (p->next != NULL) {
			p->next->xDown = p->next->xDown + p->next->dx;  // x����

			p = p->next;
		}
	}
	return result2;
}