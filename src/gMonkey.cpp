#include "gMonkey.h"

//<----------Object Class----------
gMonkey::gMonkey() : BaseObject(){
    posX = gMonkey_Stable_PosX;
    posY = gMonkey_Stable_PosY;
}

gMonkey::~gMonkey(){
    BaseObject::free();
    posX = 0;
    posY = 0;
}

void gMonkey::render(SDL_Renderer* gRenderer, SDL_Rect* clip){
    BaseObject::render(gRenderer, posX, posY, MONKEY_WIDTH, MONKEY_HEIGHT, clip);
}

int gMonkey::getPosX(){
    return posX;
}

int gMonkey::getPosY(){
    return posY;
}

void gMonkey::setPosX(int posX){
    this->posX = posX;
}

void gMonkey::setPosY(int posY){
    this->posY = posY;
}

//<----------Function---------
void setMonkeyPos(gMonkey &gMonkey_Texture,pair <int, int> gMonkey_Pos){
    gMonkey_Texture.setPosX(gMonkey_Pos.first);
    gMonkey_Texture.setPosY(gMonkey_Pos.second);
}
