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
    ObstacleWidth = OBSTACLE_WIDTH[ID];
    updateY();
    updateX();

}

void Obstacle::updateY(){
    posY_Level = rand()%SCREEN_LEVEL_COUNT;
    posY = OBSTACLE_POSY[posY_Level];
}

void Obstacle::updateX(){

    int PATH_ID = rand()%2;
    if (posY_Level == POSY_AIR_ID) PATH_ID += 2;
    if (PathPosX_Carry[PATH_ID] < SCREEN_WIDTH) posX = -SCREEN_WIDTH;

    else {
        int mod = PATH_WIDTH[PATH_ID] - ObstacleWidth + 1;
        posX = rand()%(mod) + PathPosX_Carry[PATH_ID];
        if (posX <= SCREEN_WIDTH) posX = -SCREEN_WIDTH;
    }

     for (int Level = 0; Level < SCREEN_LEVEL_COUNT; ++Level)
        for (int i = 0; i < OBSTACLE_COUNT; ++i){

        double OLD_POSX = ObstaclePosX_Carry[Level][i];
        double OLD_POSX_END = OLD_POSX + ObstacleWidth;

        if((posX + ObstacleWidth >= OLD_POSX && posX <= OLD_POSX_END) ||
           (posX <= OLD_POSX_END && posX + ObstacleWidth >= OLD_POSX)){
               posX = -SCREEN_WIDTH;
               break;
           }
    }
    ObstaclePosX_Carry[posY_Level][ID] = posX;
}


void Obstacle::render(SDL_Renderer* gRenderer, int wSize, int hSize){
    BaseObject::render(gRenderer, posX, posY, wSize, hSize);
}

void Obstacle::Move(){
    posX -= MONKEY_RUNNING_SPEED;
    ObstaclePosX_Carry[posY_Level][ID] = posX;
    if(posX < -ObstacleWidth){
        updateY();
        updateX();
    }
}

void Obstacle::Handle_Monkey(){
    //cout << gMonkey_Pos.second << " " << posY <<  "\n";   //debug only

    int monkey_border = 60;

    if ((gMonkey_Pos.second <= posY + OBSTACLE_HEIGHT) && ((gMonkey_Pos.second + MONKEY_HEIGHT) >= (posY + MAX_OBSTACLE_HEIGHT/2))){

        if ((gMonkey_Pos.first + MONKEY_WIDTH - monkey_border) >= posX && gMonkey_Pos.first + monkey_border <= posX + ObstacleWidth ) {
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
















