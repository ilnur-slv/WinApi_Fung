#ifndef _Function_
#define _Function_

#include <windows.h>
#include "GameClass.h"

void Press(Player&);
void Draw(Player&);
void Draw_Background();
void Picture(COLORREF);
void hsv_to_rgb (int,int,int,int&,int&,int&);
void rgb_to_hsv (int,int,int,int&,int&,int&);
COLORREF* ValueColor(int,int,int);
COLORREF* ColorType(int);
LPCSTR itos(int);
int ilength(int);

void Press(Player &A){
	if(A.Pr()==0){
		if ( GetAsyncKeyState( A.Left() ) ) A.LeftRotate(); else A.NotLeftRotate();
		if ( GetAsyncKeyState( A.Right() ) ) A.RightRotate(); else A.NotRightRotate();
	}
	A.Pr((A.Pr()==3)?0:A.Pr()+1);
}
void Draw(Player &A){
	Press(A);
	A.Draw();
}
void Draw_Background()
{

}
void Picture(COLORREF *color){
	int x=0;
	for(int k=0; k<10; ++k)
	{
		for(int i=x; i<x+10; ++i)
		{
			for(int j=0; j<10; ++j)
			{
				SetPixel(hdcMem,i,j,color[k]);
			}
		}
		x+=10;
	}
}
void hsv_to_rgb ( int i_hue, int sat, int val, int &r, int &g, int &b){
	int ii;
	double fr, hue;
	unsigned int c1, c2, c3;

	if (!sat)
		r = g = b = val;
	else
	{
		while (i_hue >= 360)
			i_hue -= 360;

		hue = i_hue;
		ii = (int)(hue /= 60.0);
		fr = hue - ii;
		c1 = (val * (255 - sat)) / 255;
		c2 = (val * (255 - sat * fr)) / 255;
		c3 = (val * (255 - sat * (1.0 - fr))) / 255;

		switch (ii)
		{
		case 0: r = val; g = c3; b = c1; break;
		case 1: r = c2; g = val; b = c1; break;
		case 2: r = c1; g = val; b = c3; break;
		case 3: r = c1; g = c2; b = val; break;
		case 4: r = c3; g = c1; b = val; break;
		case 5: r = val; g = c1; b = c2; break;
		}
	}
}
void rgb_to_hsv ( int r, int g, int b, int &hue, int &sat, int &val){
	double h, rc, gc, bc, dmax;
	unsigned int s, v;
	unsigned int minc, maxc;

	maxc = (r > g) ? ((r > b) ? r : b) : ((g > b)? g : b);
	minc = (r < g) ? ((r < b) ? r : b) : ((g < b)? g : b);

	s = 0; // Насыщенность
	if (maxc)
	{
		s = (maxc - minc) * 255 / maxc;
	}
	sat = s;
	val = maxc;

	if (!s)
	{ // Ахроматический цвет
		hue = 0;
	}
	else
	{ // Хроматический цвет
		dmax = maxc - minc;
		rc = (maxc - r) / dmax; /* rc - удаленность */
		gc = (maxc - g) / dmax; /* цвета от красного */
		bc = (maxc - b) / dmax;
		if (r == maxc)
		{ // Цвет между желтым и пурпурным
			h = bc - gc;
		}
		else if (g == maxc)
		{ // Цвет между голубым и желтым
			h = 2 + rc - bc;
		}
		else
		{ // Цвет между пурпурным и голубым
			h = 4 + gc - rc;
		}
		h *= 60.0;
		if (h < 0.0)
		{
			h += 360.0;
		}
		hue = h;
		if (hue == 360)
		{
			hue = 0;
		}
	}
}
COLORREF* ValueColor(int r, int g, int b){
	COLORREF* color = new COLORREF[10];
	int h,s,v;
	for(int i=0; i<10; ++i)
	{
		color[i] = RGB(r,g,b);
		rgb_to_hsv(r,g,b,h,s,v);
		hsv_to_rgb(h,s,(v-25 >= 0)?(v-25):(0),r,g,b);
	}

	return color;
}
COLORREF* ColorType(int i){	return ValueColor(r[i],g[i],b[i]); }
LPCSTR itos(int x){
	LPCSTR buf;
	char str[10];
	itoa(x,str,10);
	for(int i=0; i<10; ++i) if(str[i] <'0' || str[i]>'9') str[i] = '/0';
	buf = str;
	return buf;
}
int ilength(int x){
	if(x<10) return 1;
	if(x<100) return 2;
	if(x<1000) return 3;
	if(x<10000) return 4;
	if(x<100000) return 5;
	if(x<1000000) return 6;
	return 0;
}

#endif