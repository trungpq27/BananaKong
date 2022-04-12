#include "HigherPath.h"

HigherPath::HigherPath(int ID, pair<double, double> *PathPosX_Carry) : BaseObject(){
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
    updateX(posX, PathPosX_Carry);
}

HigherPath::~HigherPath(){
    BaseObject::free();
    posX = 0;
    posY = 0;
    ID = 0;
    pathWidth = 0;
}

void HigherPath::updateX(double &posX, pair<double, double> *PathPosX_Carry){

    posX = rand() % (PATH_SCREEN_SPACING) + SCREEN_WIDTH;
    double posX_End = posX + pathWidth;

    int ID_Col = (ID % 2) ? (ID + 1) : (ID - 1);

    if ((posX >= PathPosX_Carry[ID_Col].first && posX <= PathPosX_Carry[ID_Col].second)
        || (posX <= PathPosX_Carry[ID_Col].first && posX_End >= PathPosX_Carry[ID_Col].first)){
         posX = PathPosX_Carry[ID_Col].second + PATH_SCREEN_SPACING + (rand() % PATH_SCREEN_SPACING);
         posX_End = posX + pathWidth;
    }

    PathPosX_Carry[ID] = make_pair(posX, posX_End);
}

void HigherPath::render(SDL_Renderer* gRenderer, int wSize, int hSize){
    BaseObject::render(gRenderer, posX, posY, wSize, hSize);
}

void HigherPath::Move(double speed, pair<double, double> *PathPosX_Carry){

    posX -= speed;
    PathPosX_Carry[ID].first -= speed;
    PathPosX_Carry[ID].second -= speed;
    if(posX < -pathWidth) updateX(posX, PathPosX_Carry);
}

double HigherPath::getPosX(){
    return posX;
}

double HigherPath::getPosY(){
    return posY;
}
