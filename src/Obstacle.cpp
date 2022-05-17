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
    gMonkey_Obstacle_PosY = 0;
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
    gMonkey_Obstacle_PosY = posY - MONKEY_HEIGHT + 10;
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

    int monkey_border = 60;
    if (gMonkeyState == STATE_RUN) monkey_border = 30;
    if ((gMonkey_Pos.second + 10 <= posY + OBSTACLE_HEIGHT) && ((gMonkey_Pos.second + MONKEY_HEIGHT) >= (posY + MAX_OBSTACLE_HEIGHT/2))){

        if ((gMonkey_Pos.first + MONKEY_WIDTH - monkey_border) >= posX && gMonkey_Pos.first + monkey_border <= posX + ObstacleWidth ) {
            game_over = 1;
        }
    }

    double posX_End = posX + ObstacleWidth;

    if ((gMonkey_Pos.first + MONKEY_WIDTH - 20) >= posX && gMonkey_Pos.first + 50 <= posX_End){
        if (gMonkey_Pos.second >= gMonkey_Obstacle_PosY && gMonkey_Pos.second <= gMonkey_Obstacle_PosY + MONKEY_JUMPING_SPEED){
            if (gMonkeyState == STATE_FALLNPR || gMonkeyState == STATE_FALLPARA){
                JumpBreak = 0;
                gMonkey_Pos.second = gMonkey_Obstacle_PosY;
                gMonkeyState = STATE_RUN;
                gMonkey_PosY_ID = POSY_ON_OBSTACLE_ID;
            }
        }
    }
    else if((gMonkey_Pos.first + 50 > posX_End) && (gMonkey_Pos.first <= posX_End)){
            gMonkey_PosY_ID = POSY_GROUND_ID;
            if (gMonkeyState == STATE_RUN && gMonkey_Pos.second == gMonkey_Obstacle_PosY){
                gMonkey_Pos.second += MONKEY_JUMPING_SPEED;
                gMonkeyState = STATE_FALLNPR;
                gMonkey_PosY_ID = POSY_GROUND_ID;
            }
    }
}


double Obstacle::getPosX(){
    return posX;
}

double Obstacle::getPosY(){
    return posY;
}
















