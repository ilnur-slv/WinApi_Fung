#ifndef _LocalV_
#define _LocalV_

#include <windows.h>
#include "functions.h"
#include <cmath>
#include <math.h>
// main color //
int r[] = {170, 12  , 210, 194};
int g[] = {35 , 222 , 5  , 170};
int b[] = {228, 122 , 0  , 105};
//

COLORREF* ValueColor(int,int,int);
COLORREF* ColorType(int);

HDC hdc;
PAINTSTRUCT ps;
RECT Rect;
HDC hdcMem;
HBITMAP hbmMem;
HANDLE hOld;
HBRUSH hBrush;

class Player;
class HeadData;
class Stone;
class Nps;

class Stone{
private:

public:

};
class HeadData{
private:
	int _height;
	int _width;
	int _dt;
public:
	HeadData(int h = 640, int w = 800, int sec = 20){ _height = h; _width = w; _dt = sec; }
	int height(){ return _height; }
	int width(){ return _width; }
	int dt(){ return _dt; }
};
class Player{
private:
	COLORREF *rgb;
	int x;
	int y;
	int wl;
	int wr;
	int pr; //—ила нажати€ клавиш
	int  fi; //¬ектор
	int old_posx[6];
	int old_posy[6]; //сохран€ем старые позиции игрока
	char LeftPress;
	char RightPress;
	static Nps *nps;
public:
	Player(int xx = 320, int yy = 400, char Left = (VK_LEFT), char Right = (VK_RIGHT), COLORREF *_rgb = ColorType(0)){
		rgb = _rgb;
		x = xx; y = yy;
		wl = 3; wr = 3;
		pr = 0;
		fi = 0;
		LeftPress = Left;
		RightPress = Right;
	}

	void NpsInit(Nps *np){ nps = np; }

	void Wind(int &_x, int &_y){
	if(fi==0){_x=0;_y=-3;}
	if(fi==1){_x=-1;_y=-3;}
	if(fi==2){_x=-2;_y=-2;}
	if(fi==3){_x=-3;_y=-1;}
	if(fi==4){_x=-3;_y=0;}
	if(fi==5){_x=-3;_y=1;}
	if(fi==6){_x=-2;_y=2;}
	if(fi==7){_x=-1;_y=3;}
	if(fi==8){_x=0;_y=3;}
	if(fi==9){_x=1;_y=3;}
	if(fi==10){_x=2;_y=2;}
	if(fi==11){_x=3;_y=1;}
	if(fi==12){_x=3;_y=0;}
	if(fi==13){_x=3;_y=-1;}
	if(fi==14){_x=2;_y=-2;}
	if(fi==15){_x=1;_y=-3;}
	}
	char Left(){ return LeftPress; }
	char Right(){ return RightPress; }
	int Pr(int x = -1){ if(x != -1) pr = x; return pr; }
	void LeftRotate(){
		wl=(wl==9)?9:wl+1; wr=3; fi = ((fi+int(wl/3))>15)?(fi+int(wl/3)-15):(fi+int(wl/3));
	}
	void NotLeftRotate(){ wl = 3; }
	void RightRotate(){
		wr=(wr==9)?9:wr+1; wl=3; fi = ((fi-int(wr/3))<0)?(16+(fi-int(wr/3))):(fi-int(wr/3));
	}
	void NotRightRotate(){ wr = 3; }
	void Draw(){
		int _x,_y;
		Wind(_x,_y);
		
		for(int i=5;i>0;--i) // сохран€ем старые позиции игрока
		{
			old_posx[i] = old_posx[i-1];
			old_posy[i] = old_posy[i-1];
		}

		x+=_x;
		y+=_y;
		old_posx[0] = x;
		old_posy[0] = y;

		if(x>800) x=0;
		if(y>640) y=0;
		if(x<0) x=800;
		if(y<0) y=640;

		for(int k=5; k>=0; --k)
		for(int i=0; i<6-k; ++i)
		{
			HPEN hPen = CreatePen(PS_SOLID,1,rgb[i]);
			SelectObject(hdcMem, hPen);
			Arc(hdcMem,old_posx[k]-i,old_posy[k]-i,old_posx[k]+i,old_posy[k]+i,0,0,0,0);
			DeleteObject(hPen);
		}
	}
	int _fi(){ return fi; }
	int _x(){ return x; }
	int _y(){ return y; }
};
class Nps{
private:
	int x;
	int y;
	int fi;
	int v1;
	int v2;
	static Player *player;
public:
	Nps(int _x = 200, int _y = 400, int _v1 = 3, Player *pl = NULL){ fi=0; v2=0; x=_x; y=_x; v1=_v1; player = pl;}
	bool Speed(){
		if( (v1 == 3) && (v2 == 2 || v2 == 4 || v2 == 6) ){ v2 = (v2 == 6)?0:v2+1; return false; }
		if( (v1 == 4) && (v2 == 3 || v2 == 6) ){ v2 = (v2 == 6)?0:v2+1; return false; }
		if( (v1 == 5) && (v2 == 4) ){ v2 = (v2 == 6)?0:v2+1; return false; }
		if( (v1 == 6) ) return true;
		return true;
	}
	void Wind(int &_x, int &_y){
		if(fi==0){_x=0;_y=-3;}
		if(fi==1){_x=-1;_y=-3;}
		if(fi==2){_x=-2;_y=-2;}
		if(fi==3){_x=-3;_y=-1;}
		if(fi==4){_x=-3;_y=0;}
		if(fi==5){_x=-3;_y=1;}
		if(fi==6){_x=-2;_y=2;}
		if(fi==7){_x=-1;_y=3;}
		if(fi==8){_x=0;_y=3;}
		if(fi==9){_x=1;_y=3;}
		if(fi==10){_x=2;_y=2;}
		if(fi==11){_x=3;_y=1;}
		if(fi==12){_x=3;_y=0;}
		if(fi==13){_x=3;_y=-1;}
		if(fi==14){_x=2;_y=-2;}
		if(fi==15){_x=1;_y=-3;}
	}
	void Rotate(){

	}
};

HeadData Window;
Player player[3] = {Player(410,320,VK_LEFT,VK_RIGHT,ColorType(0)), Player(390,320,'A','D',ColorType(1)), Player(410,320,VK_LEFT,VK_RIGHT,ColorType(0))};
Nps *nps = new Nps(500,400,3,player);

#endif