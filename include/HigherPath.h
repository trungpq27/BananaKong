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

static pair<int, int> PathPosX_Carry[HIGHER_PATH_COUNT+1];

//-----Path PosY-----
const int HIGH_PATH_X1_POSY = 434;
const int HIGH_PATH_X2_POSY = 260;

const int PATH_SCREEN_SPACING = 500;
const int UP_PATH1_HEIGHT = 160;
const int UP_PATH1_WIDTH = UP_PATH1_HEIGHT*2.54;

const int UP_PATH2_HEIGHT = 160;
const int UP_PATH2_WIDTH = UP_PATH2_HEIGHT*4.565;

const int AIR_PATH1_HEIGHT = 55;
const int AIR_PATH1_WIDTH = AIR_PATH1_HEIGHT*7.3125;

const int AIR_PATH2_HEIGHT = 55;
const int AIR_PATH2_WIDTH = AIR_PATH2_HEIGHT*13.125;

class HigherPath
{
    private:
        SDL_Texture* HigherPath_Texture;
        int posX;
        int posY;
        int pathWidth;
        int ID;

    public:
        HigherPath();

        HigherPath(int pathWidth);

        ~HigherPath();

        void free();

        void updateX(int &posX);

        bool loadFromFile(std::string path, SDL_Renderer *gRenderer);

        void render(SDL_Renderer* gRenderer, int wSize, int hSize);

        int getPosX();

        int getPosY();

        void Move(int speed);
};

#endif // HIGHERPATH_H
