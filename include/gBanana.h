#ifndef GBANANA_H
#define GBANANA_H

#include "BaseFunc.h"
#include "BaseObj.h"
#include "Obstacle.h"
#include "gMonkey.h"


const int BANANA_HEIGHT = 30;
const int BANANA_WIDTH = BANANA_HEIGHT*1.348;
const int BANANA_SPACING = 300;

class gBanana : public BaseObject
{
    private:
        double posX;
        int posY;
        int Y_ID;
        int Amount;
        int Banana_Sum;

    public:
        gBanana(list<pair<double, int>> &BananaPos);
        ~gBanana();

        void updateY();

        void updateX(double &PosX, list<pair<double, int>> &BananaPos);

        void render(SDL_Renderer* gRenderer, int wSize, int hSize, double speed, list<pair<double, int>> &BananaPos);

        void Handle_Monkey(pair <int, int> gMonkey_Pos, list<pair<double, int>> &BananaPos, int &Banana_Score);
};

#endif // GBANANA_H
