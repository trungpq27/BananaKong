#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "BaseObj.h"
#include "BaseFunc.h"
#include "HigherPath.h"

//-----ID int Intenger-----
const int STONE_PIG_ID = 1;
const int TENT_ID = 2;
const int OBSTACLE_COUNT = 2;

//-----Obstacle PosY-----
const int OBSTACLE_POSY_LEVEL_COUNT = 3;
const int OBSTACLE_POSY[OBSTACLE_POSY_LEVEL_COUNT] = {473,335,159};
//---Level ID---
const int POSY_GROUND_ID = 0;
const int POSY_UP_ID = 1;
const int POSY_AIR_ID = 2;

static pair <int, int> ObstaclePosX_Carry [OBSTACLE_POSY_LEVEL_COUNT][OBSTACLE_COUNT+1];

//-----Obstacle Render Info-----
const int OBSTACLE_SCREEN_SPACING = 500;
const int STONE_PIG_HEIGHT = 120;
const int STONE_PIG_WIDTH = STONE_PIG_HEIGHT*1.719;

const int TENT_HEIGHT = 120;
const int TENT_WIDTH = TENT_HEIGHT*1.946;


class Obstacle : public BaseObject{
    private:
        double posX;
        double posY;
        int posY_Level;
        int ObstacleWidth;
        int ID;

    public:
        Obstacle(int ID, pair<double, double> *PathPosX_Carry);

        ~Obstacle();

        void updateX(double &posX, pair<double, double> *PathPosX_Carry);

        void updateY(double &posY, int &posY_Level);

        void render(SDL_Renderer* gRenderer, int wSize, int hSize);

        void Move(double speed, pair<double, double> *PathPosX_Carry);

        double getPosX();

        double getPosY();
};

#endif // OBSTACLE_H
