#include "GameClass.h"

void main(){

player = new Player[3];
player[0] = Player(410,320,VK_LEFT,VK_RIGHT,ColorType(0),nps);
player[0] = Player(390,320,'A','D',ColorType(1),nps);
player[0] = Player(410,320,VK_LEFT,VK_RIGHT,ColorType(2),nps);
nps = new Nps(500,400,3,player);

}