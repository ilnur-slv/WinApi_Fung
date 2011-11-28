#include "GameClass.h"

void main(){

Window = new HeadData(640,800,20,2);
player = new Player[3];
player[0] = Player(410,320,VK_LEFT,VK_RIGHT,ColorType(0));
player[0] = Player(390,320,'A','D',ColorType(1));
player[0] = Player(410,320,VK_LEFT,VK_RIGHT,ColorType(2));
nps = new Nps(500,400,3,player);

}