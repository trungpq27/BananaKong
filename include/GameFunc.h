#ifndef GAMEFUNC_H
#define GAMEFUNC_H

#include "gMonkey.h"
#include "BaseFunc.h"
#include "BaseObj.h"
#include "Background.h"
#include "HigherPath.h"
#include "Obstacle.h"
#include "gText.h"


const int BreakDistance = 50;

const int gMonkey_X1_PosY = HIGH_PATH_X1_POSY - MONKEY_HEIGHT + MONKEY_BORDER + UP_PATH_BORDER;
const int gMonkey_X2_PosY = HIGH_PATH_X2_POSY - MONKEY_HEIGHT + MONKEY_BORDER + AIR_PATH_BORDER;


string longLongToString(long long x);

void gMonkeyHandleMoving();

void gMonkeyHandleHigherPath(int &gMonkeyState, pair<int, int> &gMonkey_Pos, pair<double, double> *PathPosX_Carry, int &FallTo_Pos, int MONKEY_JUMPING_SPEED, int &JumpBreak);

#endif // GAMEFUNC_H
