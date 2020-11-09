#pragma once
#include "Point.h"
#include "stdio.h"
#include "string.h"
#include "Edge.h"
#include "glut.h"
#include "struct.h"

#define scannerNumber 5// 扫描线数量

class Graphic {
	public:
		Edge edgeStruct[scannerNumber] = { 0, 0, 0, NULL };  // 结构

	public:
		Graphic();  // 构造函数，生成初始化ET表
		result Filling();  // 填充函数
};

