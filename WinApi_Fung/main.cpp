#include <windows.h>
#include <string>
#include "functions.h"
#include "LocalVariables.h"
using namespace std;

LRESULT CALLBACK MyWindowFunction(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode){
	WNDCLASS wcl;

	memset(&wcl,0,sizeof(WNDCLASS));

	wcl.hInstance=hThisInst;
	wcl.lpszClassName="OurWindowClass";
	wcl.lpfnWndProc=MyWindowFunction;
	wcl.style=0;
	wcl.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wcl.hCursor=LoadCursor(NULL, IDC_ARROW);
	wcl.lpszMenuName=NULL;

	wcl.hbrBackground=0;
	if(!RegisterClass(&wcl)){return 0;}

	HWND hwnd=CreateWindow("OurWindowClass",
		"Simple Window",
		WS_OVERLAPPEDWINDOW,
		0,0,
		800,
		640,
		HWND_DESKTOP,
		NULL,
		hThisInst,
		NULL
		);

	ShowWindow(hwnd,nWinMode);
	UpdateWindow(hwnd);

	MSG msg;
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
	//if(hPrevInst!=NULL){return 0;}
}

LRESULT CALLBACK MyWindowFunction(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	switch(message){
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}
		case BN_CLICKED:
			break;
		case WM_PAINT:
			hdc=BeginPaint(hwnd, &ps);
			

			hdcMem = CreateCompatibleDC(hdc);
			hbmMem = CreateCompatibleBitmap(hdc,Window.width(), Window.height());
			hOld   = SelectObject(hdcMem, hbmMem);
			hBrush=CreateSolidBrush(RGB(0,0,0));
		    SelectObject(hdcMem,hBrush);
			Rectangle(hdcMem,0,0,Window.width(), Window.height());

			Draw(One);
			Draw(Two);

			Draw_Background();

			Picture(ColorType(2));

			BitBlt(hdc, 0, 0, Window.width(), Window.height(), hdcMem, 0, 0, SRCCOPY);

			Sleep(Window.dt());

			SelectObject(hdcMem, hOld);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);

			InvalidateRect(hwnd,NULL,1);
			EndPaint(hwnd, &ps);
			break;
		default:
			{
				return DefWindowProc(hwnd,message,wParam,lParam);
			}
	}
}