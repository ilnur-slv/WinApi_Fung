#include <windows.h>
#include <string>
#include "GameClass.h"
#include "functions.h"
using namespace std;

#define IDC_B1 (1234)
#define IDC_B2 (1235)
#define IDC_B3 (1236)
#define IDC_B4 (1237)

HWND hButton1, hButton2, hButton3, hButton4;

LRESULT CALLBACK MyWindowFunction(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode){
	// Создаем игрока и декорации
	player = new Player[3];
	player[0] = Player(410,320,VK_LEFT,VK_RIGHT,ColorType(0),nps);
	player[1] = Player(390,320,'A','D',ColorType(1),nps);
	player[2] = Player(400,320,'J','L',ColorType(2),nps);
	nps = new Nps(500,400,5,player,ColorType(3));
	Window.menu(1);
	//

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
		Window.width(),
		Window.height(),
		HWND_DESKTOP,
		NULL,
		hThisInst,
		NULL
		);

	hButton1 = CreateWindow("BUTTON", "Repaint", WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
	350, 200, 100, 24, hwnd, (HMENU)IDC_B1, NULL, NULL);

	hButton1 = CreateWindow("BUTTON", "Repaint", WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
	350, 250, 100, 24, hwnd, (HMENU)IDC_B2, NULL, NULL);

	hButton1 = CreateWindow("BUTTON", "Repaint", WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
	350, 300, 100, 24, hwnd, (HMENU)IDC_B3, NULL, NULL);

	hButton1 = CreateWindow("BUTTON", "Repaint", WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
	350, 350, 100, 24, hwnd, (HMENU)IDC_B4, NULL, NULL);

	ShowWindow(hwnd,SW_SHOW);
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
		case WM_COMMAND:
			{
				int idButton = (int) LOWORD(wParam); // идентификатор, который указан в CreateWindowEx
				if(idButton == IDC_B1)
				{
					Window.menu(0);
				}
				break;
			}
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}
		case BN_CLICKED:
			break;
		case WM_PAINT:
			//--Рисуем игру--
			if(GetAsyncKeyState(27)){
				Window.menu((Window.menu()==1)?0:1);
				if(Window.menu() == 0) UpdateWindow(hwnd);
			}
			if(Window.menu() == 0){

				hdc=BeginPaint(hwnd, &ps);
				hdcMem = CreateCompatibleDC(hdc);
				hbmMem = CreateCompatibleBitmap(hdc,Window.width(), Window.height());
				hOld   = SelectObject(hdcMem, hbmMem);
				hBrush=CreateSolidBrush(RGB(0,0,0));
				SelectObject(hdcMem,hBrush);
			
				Rectangle(hdcMem,0,0,Window.width(), Window.height());

				for(int i=0; i<Window.numberPlayer(); ++i)
				{
					Draw(player[i]);
					PrintText(5,5+i*15,itos(Window.scPrint(i)),i);
				}
				nps->Draw();
				Draw_Background();
			
				//---------------
				BitBlt(hdc, 0, 0, Window.width(), Window.height(), hdcMem, 0, 0, SRCCOPY);

				Sleep(Window.dt());

				SelectObject(hdcMem, hOld);
				DeleteObject(hbmMem);
				DeleteDC(hdcMem);

				InvalidateRect(hwnd,NULL,1);
				EndPaint(hwnd, &ps);
			}
			break;
		default:
			{
				return DefWindowProc(hwnd,message,wParam,lParam);
			}
	}
}