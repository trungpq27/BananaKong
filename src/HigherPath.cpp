#include "HigherPath.h"

HigherPath::HigherPath() : BaseObject(){
}

HigherPath::~HigherPath(){
    BaseObject::free();
    posX = 0;
    posY = 0;
    ID = 0;
    pathWidth = 0;
}

void HigherPath::init(int ID){

    this->ID = ID;
    if (ID == UP_PATH1_ID){
        pathWidth = UP_PATH1_WIDTH;
        posY = HIGH_PATH_X1_POSY;
    }

    if (ID == UP_PATH2_ID){
        pathWidth = UP_PATH2_WIDTH;
        posY = HIGH_PATH_X1_POSY;
    }

    if (ID == AIR_PATH1_ID){
        pathWidth = AIR_PATH1_WIDTH;
        posY = HIGH_PATH_X2_POSY;
    }
    if (ID == AIR_PATH2_ID){

        pathWidth = AIR_PATH2_WIDTH;
        posY = HIGH_PATH_X2_POSY;
    }
    updateX();

}

void HigherPath::updateX(){

    posX = rand() % (PATH_SCREEN_SPACING) + SCREEN_WIDTH;
    double posX_End = posX + pathWidth;

    int ID_Col = (ID == 1 || ID == 3) ? ID - 1 : ID + 1;

    double OldPosX = PathPosX_Carry[ID_Col];
    double OldPosX_End = OldPosX + PATH_WIDTH[ID_Col];

    if ((posX >= OldPosX && posX <= OldPosX_End)
        || (posX <= OldPosX && posX_End >= OldPosX)){
         posX = OldPosX_End + PATH_SCREEN_SPACING + (rand() % PATH_SCREEN_SPACING);
         posX_End = posX + pathWidth;
    }

    PathPosX_Carry[ID] = posX;
}

void HigherPath::render(SDL_Renderer* gRenderer, int wSize, int hSize){
    BaseObject::render(gRenderer, posX, posY, wSize, hSize);
}

void HigherPath::Move(){

    posX -= MONKEY_RUNNING_SPEED;
    PathPosX_Carry[ID] -= MONKEY_RUNNING_SPEED;
    if(posX < -pathWidth) updateX();
}

double HigherPath::getPosX(){
    return posX;
}

double HigherPath::getPosY(){
    return posY;
}
