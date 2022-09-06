#include<unordered_map>
#include<windows.h>
#include<windowsx.h>
#include<math.h>
#include<stdio.h>
#include <string>
#include <string.h>
#include<typeinfo>
#include <io.h>  
#include <iostream>
#include <vector>
//��̬�����

#include "F:/����/����/Shape/Shape.h"
#pragma comment(lib,"F:/����/����/Shape/Debug/SHAPE.lib")

using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



//��������
Shape* shape[100];
ShapePackage* shapePackage[10];
int kindnumber = 0;
int shapenum = 0;  //ͼ������

vector<string> files;

Builder* builder;
Painter* painter;

//typedef void(*FUNCSP)();
//typedef ShapePackage* (*FUNGSP)(int i);
//HINSTANCE hActive = LoadLibrary(TEXT("F:/����/����/MyFuctionDLL/Debug/MyFuctionDLL.dll"));
//FUNCSP createShapePackage = (FUNCSP)GetProcAddress(hActive, "CreateShapePackage");
//FUNGSP getShapePackage = (FUNGSP)GetProcAddress(hActive, "GetShapePackage");

char* savePath = "F:/����/����/newhuaban/Debug/Save/save01.txt";  //�Լ�����Ŀ¼  exe�ļ���ʱִ�в�������Ϊexe�ļ�·����cpp�ļ�·����ͬ��������Ҫ����·��

void InitShapePackage() {
	//char* filePath = "./Debug/MyDll";//�Լ�����Ŀ¼  
	char* filePath = "F:/����/����/newhuaban/Debug/MyDll";//�Լ�����Ŀ¼  exe�ļ���ʱִ�в�������Ϊexe�ļ�·����cpp�ļ�·����ͬ��������Ҫ����·��
	long   hFile = 0;
	//�ļ���Ϣ������һ���洢�ļ���Ϣ�Ľṹ��  
	struct _finddata_t fileinfo;
	string p;//�ַ��������·��
	if ((hFile = _findfirst(p.assign(filePath).append("\\*.dll").c_str(), &fileinfo)) != -1)//�����ҳɹ��������
	{
		do
		{
			files.push_back(p.assign(filePath).append("\\").append(fileinfo.name));
		} while (_findnext(hFile, &fileinfo) == 0);
		//_findclose������������
		_findclose(hFile);
	}
	kindnumber = files.size();
	typedef ShapePackage* (*FUNGSP)();
	HINSTANCE hShape;
	FUNGSP GetPackage;
	for (int i = 0; i < files.size(); i++)
	{
		hShape = LoadLibrary(files[i].c_str());
		GetPackage = (FUNGSP)GetProcAddress(hShape, "GetPackage");
		shapePackage[i] = GetPackage();
		//shapePackage[i]->Initialize();
	}
}

void delete_shape(int num) {
	HPEN delete_pen = CreatePen(PS_SOLID, shape[num]->pen_width, RGB(255, 255, 255));
	shape[num]->draw(delete_pen);	
}

void LoadAllShape(HWND hwnd) {
	int kind;
	for (int i = 0;i < shapenum;i++) {
		delete_shape(i);
		shape[i]->destroy();
	}
	FILE* fp = fopen(savePath, "r");
	if (fp == NULL) {

	}
	fscanf(fp, "%d", &shapenum); //����ͼ������
	for (int i = 0;i < shapenum;i++) {
		fscanf(fp, "%d", &kind);
		delete(builder);
		builder = shapePackage[kind-1]->GetBuilder();
		builder->build();
		builder->initialize(kind, hwnd);
		shape[i] = builder->returnShape();
		shape[i]->load(fp);
		shape[i]->kind = kind;
	}
	for (int i = 0;i < shapenum;i++) {
		shape[i]->draw(shape[i]->hPen);
	}
	fclose(fp);
}

void SaveAllShape() {
	FILE* fp = fopen(savePath, "w");
	if (fp == NULL) {
	}
	fprintf(fp, "%d \n", shapenum); //д�뵱ǰͼ������
	//fprintf(fp, "%d \n", kindNumber); //д�뵱ǰͼ������
	for (int i = 0;i < shapenum;i++) {
		fprintf(fp, "%d ", shape[i]->kind);
		shape[i]->save(fp);  //д��ͼ������
	}
	fclose(fp);
}


//�˶�������

class ShapeMove
{
protected:
	int shapeNumber = 0;
	Point firstPosi;
	Point lastPosi;
public:
	bool moving = false;
	void LButtonDown(LPARAM lParam) {

		if (!moving) {

			while (shapeNumber < shapenum && !shape[shapeNumber]->click(lParam)) {
				shapeNumber++;
			}
			if (shapeNumber != shapenum) {   //��ĳ��ͼ���ϣ������ƶ�״̬	
				moving = true;
				firstPosi.x = GET_X_LPARAM(lParam);
				firstPosi.y = GET_Y_LPARAM(lParam);
			}
			else           //�յ��
				shapeNumber = 0;

		}
		else {
			moving = false;
			for (int i = 0;i < shapenum;i++) {       //��ֹͼ���ƶ����¸�ͼ���ڵ��ı��ͼ��ȱʧ����������������ƶ�ͼ��������ͼ���ػ�
				if (i != shapeNumber)
					shape[i]->draw(shape[i]->hPen);
			}
			shapeNumber = 0;
		}
	};
	void MouseMoving(LPARAM lParam) {
		if (moving) {
			lastPosi.x = GET_X_LPARAM(lParam);
			lastPosi.y = GET_Y_LPARAM(lParam);
			delete_shape(shapeNumber);
			shape[shapeNumber]->move(lastPosi.x - firstPosi.x, lastPosi.y - firstPosi.y);
			shape[shapeNumber]->draw(shape[shapeNumber]->hPen);
			firstPosi.x = lastPosi.x;
			firstPosi.y = lastPosi.y;
		}
	}
};
ShapeMove* moveController = new ShapeMove;






int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)

{
	//createShapePackage();
	InitShapePackage();

	static TCHAR szAppName[] = TEXT("MyWindows");
	HWND hwnd;  //���ھ��������ָ�루���Կ�������ʵ����
	MSG msg;    //��Ϣ��һ���ṹ
	WNDCLASS wndclass;   //���崰����ṹ

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//��������     �ı䴰�ڿ���ʱ����̬�ı䴰��
	wndclass.lpfnWndProc = WndProc;  //ָ����Ӧ����Ϣ��������ַ
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	//Ԥ���Ķ���ռ䣬һ��Ϊ0
	wndclass.hInstance = hInstance;
	//Ӧ�ó����ʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//���ڵ�ͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//���ڵĹ��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//��������ɫ
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	//����������

	if (!RegisterClass(&wndclass))   //ע�ᴰ�����ҳɹ�
	{
		MessageBox(NULL, TEXT("����������"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,     //����ʵ������wndclass->hwnd
		TEXT("����"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);     //��ʾ����
	UpdateWindow(hwnd);            //���´���

	//��������


	while (GetMessage(&msg, NULL, 0, 0))    //����������Ϣ
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); //ͨ��windows���� callback wndproc
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	HDC hdc;
	HDC hdc1 = GetDC(hwnd);
	PAINTSTRUCT ps;
	RECT rect;
	static POINT Mouse_x_y;
	GetCursorPos(&Mouse_x_y);
	static  HWND  buttonDraw[10], save, load;//save_button, read_button;
	//static HWND b[5];
	switch (message)
	{
	case WM_CREATE:
		//���ư�ť
		
		for (int i = 0;i < kindnumber;i++) {
			buttonDraw[i] = CreateWindow(TEXT("Button"), shapePackage[i]->GetShapeName().c_str(),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				30, 30 + i * 70, 200, 50,
				hwnd, (HMENU)1,
				((LPCREATESTRUCT)lParam)->hInstance, NULL);
		}
		load = CreateWindow(TEXT("Button"), TEXT("Load"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			30, 380, 200, 50,
			hwnd, (HMENU)1,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);
		save = CreateWindow(TEXT("Button"), TEXT("Save"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			30, 450, 200, 50,
			hwnd, (HMENU)1,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		return 0;

	case WM_COMMAND:    //��ť�����º����Ӧ

		for (int i = 0;i < kindnumber;i++) {
			if ((HWND)lParam == buttonDraw[i]) {				
				delete(builder);
				delete(painter);
				builder = shapePackage[i]->GetBuilder();
				builder->build();
				builder->initialize(i + 1, hwnd);
				shape[shapenum] = builder->returnShape();
				painter = shapePackage[i]->GetPainter();
				painter->GetShape(shape[shapenum]);
				painter->painting = true;
				break;
			}
		}

		if ((HWND)lParam == load) {
			if (painter)
				painter->painting = false;
			LoadAllShape(hwnd);
		}

		else if ((HWND)lParam == save) {
			if (painter)
				painter->painting = false;
			SaveAllShape();
		}
		return 0;

	case WM_PAINT:  //�ػ洰��
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:    //����������
		if (painter && painter->painting == true) {     //����ǰ����˰�ť��Ļ���״̬
			painter->LButtonDown(lParam);
			if (painter->painting == false) {
				shapenum++;
			}
		}
		else     //�ǻ���״̬���ж��Ƿ��϶�ͼ��
		{
			moveController->LButtonDown(lParam);
		}
		return 0;

	case WM_MOUSEMOVE:
		if (painter && painter->painting == true) {
			painter->MouseMove(lParam);
		}
		else if (moveController && moveController->moving == true) {
			moveController->MouseMoving(lParam);
		}
		return 0;

	case WM_LBUTTONUP:
		return 0;

	case WM_LBUTTONDBLCLK:
		return 0;

	case WM_RBUTTONDOWN:
		if (painter && painter->painting == true) {
			painter->RButtonDown(lParam);
			if (painter->painting == false) {
				shapenum++;
			}
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
