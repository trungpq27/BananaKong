#ifndef GMONKEY_H
#define GMONKEY_H

#include "BaseFunc.h"
#include "BaseObj.h"

#define JumpTo max(0, gMonkey_Pos.second - jumpUpY)

//---State in Intenger---
const int GROUNDED = 1;
const int JUMP = 2;
const int FALL = 3;

//---Position---
static pair <int, int> Ground = {350,480};
static pair <int,int> gMonkey_Pos = {350,480};
const int jumpUpY = 230;

//----Pic Info---
const int Monkey_W = 100;
const int Monkey_H = 120;
const int MONKEY_WALKING_FRAME_COUNT = 4;
const int MONKEY_RUNNING_FRAME_COUNT = 8;
const int MONKEY_JUMPING_FRAME_COUNT = 1;


//<----------Object Class---------
class gMonkey : public BaseObject{

private:

    int state;

public:
    gMonkey();

    ~gMonkey();

    bool getState(int status);

    void SetState(int setTo = NULL);

    int getX();

    int getY();
};



//<----------Function---------
void MonkeyFrameControl(int &frame, double speed);
void MonkeyHandleMoving();



#endif // GMONKEY_H
