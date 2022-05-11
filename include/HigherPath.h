#ifndef HIGHERPATH_H
#define HIGHERPATH_H

#include "BaseFunc.h"
#include "BaseObj.h"

//-----ID int Intenger-----
const int UP_PATH1_ID = 0;
const int UP_PATH2_ID = 1;
const int AIR_PATH1_ID = 2;
const int AIR_PATH2_ID = 3;
const int HIGHER_PATH_COUNT = 4;

//-----Path PosY-----
const int HIGH_PATH_X1_POSY = 424;
const int HIGH_PATH_X2_POSY = 254;

//-----Path Render Info-----
const int PATH_SCREEN_SPACING = 500;
const int UP_PATH_BORDER = 13;
const int AIR_PATH_BORDER = 18;

const int UP_PATH1_HEIGHT = 170;
const int UP_PATH1_WIDTH = UP_PATH1_HEIGHT*2.0755;

const int UP_PATH2_HEIGHT = 170;
const int UP_PATH2_WIDTH = UP_PATH2_HEIGHT*3.7412;

const int AIR_PATH1_HEIGHT = 55;
const int AIR_PATH1_WIDTH = AIR_PATH1_HEIGHT*6.615;

const int AIR_PATH2_HEIGHT = 55;
const int AIR_PATH2_WIDTH = AIR_PATH2_HEIGHT*11.925;

const double PATH_WIDTH[HIGHER_PATH_COUNT] = {UP_PATH1_WIDTH, UP_PATH2_WIDTH, AIR_PATH1_WIDTH, AIR_PATH2_WIDTH};


//-----HigherPath Class-----
class HigherPath : public BaseObject
{
    private:
        double posX;
        double posY;
        int pathWidth;
        int ID;

    public:

        HigherPath();

        ~HigherPath();

        void init(int ID);

        void updateX();

        void render(SDL_Renderer* gRenderer, int wSize, int hSize);

        void Move();

        double getPosX();

        double getPosY();
};

//-----Extern in Main-----
extern HigherPath AirPath1_Texture;
extern HigherPath AirPath2_Texture;
extern HigherPath UpPath1_Texture;
extern HigherPath UpPath2_Texture;
extern double PathPosX_Carry[HIGHER_PATH_COUNT];

extern double MONKEY_RUNNING_SPEED;

#endif // HIGHERPATH_H
