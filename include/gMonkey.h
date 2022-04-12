#ifndef GMONKEY_H
#define GMONKEY_H

#include "BaseFunc.h"
#include "BaseObj.h"

//---Speed---
const double BASE_MONKEY_SPEED = 4.0;

//---State in Intenger---
const int STATE_RUN = 1;
const int STATE_JUMP = 2;
const int STATE_FALLNPR = 3;
const int STATE_FALLPARA = 4;

//---Position---
const int gMonkey_Stable_PosX = 350;
const int gMonkey_Stable_PosY = 480;
const int gMonkey_JumpTo_Y1 = 250;
const int gMonkey_JumpTo_Y2 = 120;

//----Pic Info---
const int MONKEY_WIDTH = 100;
const int MONKEY_HEIGHT = 120;
const int MONKEY_BORDER = 7;

const int MONKEY_WALKING_FRAME_COUNT = 4;
const int MONKEY_RUNNING_FRAME_COUNT = 8;
const int MONKEY_JUMPING_FRAME_COUNT = 1;
const int MONKEY_FALLNPR_FRAME_COUNT = 1;


//<----------Object Class---------
class gMonkey : public BaseObject{

private:
    int posX;
    int posY;

public:
    gMonkey();

    ~gMonkey();

    void render(SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);

    int getPosX();

    int getPosY();

    void setPosX(int posX);

    void setPosY(int posY);
};



//<----------Function---------

void setMonkeyPos(gMonkey &gMonkey_Texture,pair <int, int> gMonkey_Pos);

#endif // GMONKEY_H
