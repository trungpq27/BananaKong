#include "Obstacle.h"


//-----Object Class-----
Obstacle::Obstacle(int ID, pair<int, int> *PathPosX_Carry) : BaseObject(){
    this->ID = ID;

    if (ID == STONE_PIG_ID) ObstacleWidth = STONE_PIG_WIDTH;
    if (ID == TENT_ID) ObstacleWidth = TENT_WIDTH;

    updateY(posY, posY_Level);
    updateX(posX, PathPosX_Carry);
}

Obstacle::~Obstacle(){
    BaseObject::free();
    posX = 0;
    posY = 0;
    posY_Level = 0;
    ObstacleWidth = 0;
    ID = 0;
}

void Obstacle::updateY(int &posY, int &posY_Level){
    posY_Level = rand()%OBSTACLE_POSY_LEVEL_COUNT;
    posY = OBSTACLE_POSY[posY_Level];
}

void Obstacle::updateX(int &posX, pair<int, int> *PathPosX_Carry){

    if (posY_Level == POSY_GROUND_ID){
        posX = rand()%(OBSTACLE_SCREEN_SPACING) + SCREEN_WIDTH;
    }
    else {
        int PATH_ID = rand()%2 + 1;
        if (posY_Level == POSY_AIR_ID) PATH_ID += 2;

        if (!PathPosX_Carry[PATH_ID].first) posX = -ObstacleWidth;

        else {
            posX = rand()%(PathPosX_Carry[PATH_ID].second - PathPosX_Carry[PATH_ID].first - ObstacleWidth + 1) + PathPosX_Carry[PATH_ID].first;
            if (posX <= SCREEN_WIDTH) posX = -ObstacleWidth;
        }
    }

     for(int i = 0; i <= OBSTACLE_COUNT; ++i){
        int OLD_POSX = ObstaclePosX_Carry[posY_Level][i].first;
        int OLD_POSX_END = ObstaclePosX_Carry[posY_Level][i].second;

        if((posX >= OLD_POSX && posX <= OLD_POSX_END) || (posX <= OLD_POSX && posX+ObstacleWidth >= OLD_POSX)) posX = -ObstacleWidth;
    }

    ObstaclePosX_Carry[posY_Level][ID] = make_pair(posX, posX+ObstacleWidth);

}


void Obstacle::render(SDL_Renderer* gRenderer, int wSize, int hSize){
    BaseObject::render(gRenderer, posX, posY, wSize, hSize);
}

void Obstacle::Move(int speed, pair<int, int> *PathPosX_Carry){
    posX -= speed;
    ObstaclePosX_Carry[posY_Level][ID].first -= speed;
    ObstaclePosX_Carry[posY_Level][ID].second -= speed;
    if(posX < -ObstacleWidth){
        updateY(posY, posY_Level);
        updateX(posX, PathPosX_Carry);
    }
}

int Obstacle::getPosX(){
    return posX;
}

int Obstacle::getPosY(){
    return posY;
}
















