#ifndef GMONKEY_H
#define GMONKEY_H

#include "BaseFunc.h"
#include "BaseObj.h"
#include "HigherPath.h"
#include "gSound.h"

//---Speed---
const double BASE_MONKEY_SPEED = 4.0;
const int JUMP_BREAK_DISTANCE = 50;

//---State in Intenger---
const int STATE_RUN = 1;
const int STATE_JUMP = 2;
const int STATE_FALLNPR = 3;
const int STATE_FALLPARA = 4;

const int MONKEY_JUMP_DISTANCE = 190;

//----Pic Info---
const int MONKEY_WIDTH = 90;
const int MONKEY_HEIGHT = MONKEY_WIDTH*1.313;

const int MONKEY_WALKING_FRAME_COUNT = 4;
const int MONKEY_RUNNING_FRAME_COUNT = 8;
const int MONKEY_JUMPING_FRAME_COUNT = 1;
const int MONKEY_FALLNPR_FRAME_COUNT = 1;

//---Position---
const int MONKEY_STABLE_POSX = 280;
const int MONKEY_STABLE_POSY = 472;

const int MONKEY_POSY_LEVEL[SCREEN_LEVEL_COUNT] = {MONKEY_STABLE_POSY, HIGH_PATH_X1_POSY - MONKEY_HEIGHT + UP_PATH_BORDER, HIGH_PATH_X2_POSY - MONKEY_HEIGHT + AIR_PATH_BORDER};


//<----------Object Class---------
class gMonkey : public BaseObject{

private:
    int posX;
    int posY;

public:
    gMonkey();

    ~gMonkey();

    void render(SDL_Rect* clip = NULL);

    int getPosX();

    int getPosY();

    void setPosX(int posX);

    void setPosY(int posY);
};

//-----Declare-----
extern int gRunDistance;
extern int gMonkeyState;
extern int JumpBreak;
extern int jumpToPos;
extern bool gMonkeyOnObstacle;
extern pair <int, int> gMonkeyPos;

extern int MONKEY_RUNNING_FRAME;
extern int MONKEY_JUMPING_SPEED;
extern double MONKEY_RUNNING_SPEED;
extern int MONKEY_ANIMATION_SPEED;

extern gMonkey gMonkeyRunning_Texture;
extern gMonkey gMonkeyJumping_Texture;
extern gMonkey gMonkeyFallNPR_Texture;
extern gMonkey gMonkeyFallPARA_Texture;

extern SDL_Rect gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME_COUNT];

//-----Object Function-----
extern void gMonkeyRenderRunning();

extern void gMonkeyHandleRunning();
extern void gMonkeyHandleJumping();
extern void gMonkeyHandleFallNPR();
extern void gMonkeyHandleFallPARA();


//-----Load Media-----
extern bool isLoadMonkeyOK();
extern void closeMonkey();

#endif // GMONKEY_H
