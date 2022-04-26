#include "Obstacle.h"


//-----Object Class-----
Obstacle::Obstacle() : BaseObject(){
}

Obstacle::~Obstacle(){
    BaseObject::free();
    posX = 0;
    posY = 0;
    posY_Level = 0;
    ObstacleWidth = 0;
    ID = 0;
}

void Obstacle::init(int ID){
    this->ID = ID;

    if (ID == STONE_PIG_ID) ObstacleWidth = STONE_PIG_WIDTH;
    if (ID == TENT_ID) ObstacleWidth = TENT_WIDTH;

    updateY(posY, posY_Level);
    updateX(posX);

}

void Obstacle::updateY(double &posY, int &posY_Level){
    posY_Level = rand()%OBSTACLE_POSY_LEVEL_COUNT;
    posY = OBSTACLE_POSY[posY_Level];
}

void Obstacle::updateX(double &posX){

        int PATH_ID = rand()%2 + 1;
        if (posY_Level == POSY_AIR_ID) PATH_ID += 2;

        if (!PathPosX_Carry[PATH_ID].first) posX = -ObstacleWidth;

        else {
            int mod = PathPosX_Carry[PATH_ID].second - PathPosX_Carry[PATH_ID].first - ObstacleWidth + 1;
            posX = rand()%(mod) + PathPosX_Carry[PATH_ID].first;
            if (posX <= SCREEN_WIDTH) posX = -ObstacleWidth;
        }

     for(int i = 1; i <= OBSTACLE_COUNT; ++i){
        double OLD_POSX = ObstaclePosX_Carry[posY_Level][i].first;
        double OLD_POSX_END = ObstaclePosX_Carry[posY_Level][i].second;
        if((posX >= OLD_POSX && posX <= OLD_POSX_END) || (posX <= OLD_POSX && posX+ObstacleWidth >= OLD_POSX))
            posX = -ObstacleWidth;
    }
    ObstaclePosX_Carry[posY_Level][ID] = make_pair(posX, posX+ObstacleWidth);

}


void Obstacle::render(SDL_Renderer* gRenderer, int wSize, int hSize){
    BaseObject::render(gRenderer, posX, posY, wSize, hSize);
}

void Obstacle::Move(){
    posX -= MONKEY_RUNNING_SPEED;
    ObstaclePosX_Carry[posY_Level][ID].first -= MONKEY_RUNNING_SPEED;
    ObstaclePosX_Carry[posY_Level][ID].second -= MONKEY_RUNNING_SPEED;
    if(posX < -ObstacleWidth){
        updateY(posY, posY_Level);
        updateX(posX);
    }
}

void Obstacle::Handle_Monkey(){
    //cout << gMonkey_Pos.second << " " << posY <<  "\n";   //debug only

    int monkey_border = 30;

    if (gMonkeyState == STATE_JUMP) monkey_border = 80;

    if ((gMonkey_Pos.second <= posY + OBSTACLE_HEIGHT) && (gMonkey_Pos.second + MONKEY_HEIGHT >= posY)){
        if ((gMonkey_Pos.first + MONKEY_WIDTH - monkey_border) >= posX && gMonkey_Pos.first <= posX ) {
            game_over = 1;
        }
    }
}


double Obstacle::getPosX(){
    return posX;
}

double Obstacle::getPosY(){
    return posY;
}
















