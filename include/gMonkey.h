#ifndef GMONKEY_H
#define GMONKEY_H

#include "BaseFunc.h"
#include "BaseObj.h"
#include "HigherPath.h"

//---Speed---
const double BASE_MONKEY_SPEED = 4.0;

//---State in Intenger---
const int STATE_RUN = 1;
const int STATE_JUMP = 2;
const int STATE_FALLNPR = 3;
const int STATE_FALLPARA = 4;

//----Pic Info---
const int MONKEY_WIDTH = 100;
const int MONKEY_HEIGHT = 120;
const int MONKEY_BORDER = 7;

const int MONKEY_WALKING_FRAME_COUNT = 4;
const int MONKEY_RUNNING_FRAME_COUNT = 8;
const int MONKEY_JUMPING_FRAME_COUNT = 1;
const int MONKEY_FALLNPR_FRAME_COUNT = 1;

//---Position---
const int gMonkey_Stable_PosX = 280;
const int gMonkey_Stable_PosY = 480;
const int gMonkey_JumpTo_Y1 = 250;
const int gMonkey_JumpTo_Y2 = 120;

const int gMonkey_X1_PosY = HIGH_PATH_X1_POSY - MONKEY_HEIGHT + MONKEY_BORDER + UP_PATH_BORDER;
const int gMonkey_X2_PosY = HIGH_PATH_X2_POSY - MONKEY_HEIGHT + MONKEY_BORDER + AIR_PATH_BORDER;



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

//-----Extern in Main-----
extern int gRunDistance;
extern int gMonkeyState;
extern int JumpBreak;
extern int JumpTo_Pos;
extern int FallTo_Pos;
extern pair <int, int> gMonkey_Pos;

extern int MONKEY_RUNNING_FRAME;
extern int MONKEY_JUMPING_SPEED;
extern double MONKEY_RUNNING_SPEED;
extern int MONKEY_ANIMATION_SPEED;

extern gMonkey gMonkeyRunning_Texture;
extern gMonkey gMonkeyJumping_Texture;
extern gMonkey gMonkeyFallNPR_Texture;
extern gMonkey gMonkeyFallPARA_Texture;

extern SDL_Rect gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME_COUNT];


#endif // GMONKEY_H
