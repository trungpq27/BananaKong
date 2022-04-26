#ifndef GBANANA_H
#define GBANANA_H

#include "BaseFunc.h"
#include "BaseObj.h"
#include "Obstacle.h"
#include "gMonkey.h"
#include "gSound.h"

//-----gMonkey-----
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
        gBanana();
        ~gBanana();

        void init();

        void updateY();

        void updateX(double &PosX);

        void render(SDL_Renderer* gRenderer);

        void Handle_Monkey();
};

//-----Extern in Main-----
extern int Banana_Score;
extern gBanana gBanana_Texture;
extern list<pair<double, int>> BananaPos;

#endif // GBANANA_H
