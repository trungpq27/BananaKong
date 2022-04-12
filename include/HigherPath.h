#ifndef HIGHERPATH_H
#define HIGHERPATH_H

#include "BaseFunc.h"
#include "BaseObj.h"

//-----ID int Intenger-----
const int UP_PATH1_ID = 1;
const int UP_PATH2_ID = 2;
const int AIR_PATH1_ID = 3;
const int AIR_PATH2_ID = 4;
const int HIGHER_PATH_COUNT = 4;

//-----Path PosY-----
const int HIGH_PATH_X1_POSY = 434;
const int HIGH_PATH_X2_POSY = 260;

//-----Path Render Info-----
const int PATH_SCREEN_SPACING = 500;
const int UP_PATH_BORDER = 20;
const int AIR_PATH_BORDER = 18;

const int UP_PATH1_HEIGHT = 160;
const int UP_PATH1_WIDTH = UP_PATH1_HEIGHT*2.358;

const int UP_PATH2_HEIGHT = 160;
const int UP_PATH2_WIDTH = UP_PATH2_HEIGHT*4.147;

const int AIR_PATH1_HEIGHT = 55;
const int AIR_PATH1_WIDTH = AIR_PATH1_HEIGHT*6.615;

const int AIR_PATH2_HEIGHT = 55;
const int AIR_PATH2_WIDTH = AIR_PATH2_HEIGHT*11.925;


//-----HigherPath Class-----
class HigherPath : public BaseObject
{
    private:
        double posX;
        double posY;
        int pathWidth;
        int ID;

    public:

        HigherPath(int ID, pair<double, double> *PathPosX_Carry);

        ~HigherPath();

        void updateX(double &posX, pair<double, double> *PathPosX_Carry);

        void render(SDL_Renderer* gRenderer, int wSize, int hSize);

        void Move(double speed, pair<double, double> *PathPosX_Carry);

        double getPosX();

        double getPosY();
};

#endif // HIGHERPATH_H
