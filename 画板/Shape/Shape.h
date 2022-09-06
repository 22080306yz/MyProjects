#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include<unordered_map>
#include<windows.h>
#include<windowsx.h>
#include<math.h>
#include<stdio.h>
#include <string>
#include <string.h>
#include<typeinfo>
using namespace std;


class Point {
public:
	int x;
	int y;
};

class Shape {  //ͼ����
public:
	int kind;
	HWND hwnd;
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	int pen_width = 1;
	int pen_r = 0;
	int pen_g = 0;
	int pen_b = 0;
	bool drawover = false;

	void change_pen(int width, int r, int g, int b) {
		pen_width = width;
		pen_r = r;
		pen_g = g;
		pen_b = b;
		hPen = CreatePen(PS_SOLID, width, RGB(r, g, b));
	}
	virtual void destroy() = 0;

	virtual void move(int x, int y) = 0;      //ͼ���϶������麯��������д

	virtual void draw(HPEN hp) = 0;   //ͼ�λ��ƣ����麯��������д

	virtual bool click(LPARAM lParam) = 0; //�ж�����Ƿ���ͼ���ϣ��麯��������д

	virtual void load(FILE* fp) = 0;

	virtual void save(FILE* fp) = 0;

};

class Builder {
public:
	virtual void build() = 0;
	virtual void initialize(int k, HWND h) = 0;
	virtual Shape* returnShape() = 0;
};
class Painter {
public:
	bool painting = false;
	virtual void GetShape(Shape* s) = 0;
	virtual void LButtonDown(LPARAM lParam) = 0;
	virtual void LButtonDbClick(LPARAM lParam) = 0;
	virtual void LButtonUp(LPARAM lParam) = 0;
	virtual void RButtonDown(LPARAM lParam) = 0;
	virtual void RButtonUp(LPARAM lParam) = 0;
	virtual void MouseMove(LPARAM lParam) = 0;
};

class ShapePackage {
public:
	virtual string GetShapeName() = 0;
	virtual Builder* GetBuilder() = 0;
	virtual Painter* GetPainter() = 0;
	
};



#endif
