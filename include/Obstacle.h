#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "BaseObj.h"
#include "BaseFunc.h"
#include "HigherPath.h"
#include "gMonkey.h"

//-----Obstacle PosY-----
const int OBSTACLE_POSY[SCREEN_LEVEL_COUNT] = {473,317,153};

//-----Obstacle Render Info-----
const int OBSTACLE_HEIGHT = 120;

const int OBSTACLE_SCREEN_SPACING = 500;
const int STONE_PIG_HEIGHT = 120;
const int STONE_PIG_WIDTH = STONE_PIG_HEIGHT*1.719;

const int TENT_HEIGHT = 120;
const int TENT_WIDTH = TENT_HEIGHT*1.946;

//-----ID int Intenger-----
const int STONE_PIG_ID = 0;
const int TENT_ID = 1;
const int OBSTACLE_COUNT = 2;
const int OBSTACLE_WIDTH[OBSTACLE_COUNT] = {STONE_PIG_WIDTH, TENT_WIDTH};

const int MAX_OBSTACLE_HEIGHT = max(STONE_PIG_HEIGHT, TENT_HEIGHT);
const int MAX_OBSTACLE_WIDTH = max(STONE_PIG_WIDTH, TENT_WIDTH);



class Obstacle : public BaseObject{
    private:
        double posX;
        double posY;
        int posY_Level;
        int ObstacleWidth;
        int ID;

    public:
        Obstacle();

        ~Obstacle();

        void init(int ID);

        void updateX();

        void updateY();

        void render(SDL_Renderer* gRenderer, int wSize, int hSize);

        void Move();

        void Handle_Monkey();

        double getPosX();

        double getPosY();
};

//-----Exntern in Main-----
extern Obstacle StonePig_Texture;
extern Obstacle Tent_Texture;
extern double ObstaclePosX_Carry [SCREEN_LEVEL_COUNT][OBSTACLE_COUNT];

extern bool game_over;

#endif // OBSTACLE_H
