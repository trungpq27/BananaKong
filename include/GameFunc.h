#ifndef GAMEFUNC_H
#define GAMEFUNC_H

#include "gMonkey.h"
#include "BaseFunc.h"
#include "BaseObj.h"
#include "Background.h"
#include "HigherPath.h"
#include "Obstacle.h"
#include "gText.h"
#include "Timer.h"
#include "gBanana.h"
#include "Button.h"
#include "gSound.h"

//-----Declare Game State-----
extern bool backToMenu;
extern bool menu;
extern bool play;
extern bool quit_game;
extern bool game_over;
extern bool game_paused;
extern bool quit;
extern bool exit_game;

extern int ScoreBoard_PosY;

//----------Function----------

string longLongToString(long long x);

void GameInitEverything();

void HandleMenu();

//-----gMonkey-----

void gMonkeyHandleChangeSpeed();

void gMonkeyHandleMoving();

void gMonkeyHandleHigherPath();

void gMonkeyHandleMoving();

//-----Game-----
void UpdateHighScore(int &BestDistance, int &BestBanana);

void DeathScreenShot();

void handleTopLeftScore();

//-----Stop Function-----
void handleDeathFuncion(SDL_Event e_mouse);

void HandlePauseFunction(SDL_Event e_mouse);

void HandleStopFunction();

//-----Stop Screen-----
void getDeathScore();

void handleDeathFloatingObject();

void HandlePauseFloatingObject();

void HandleStopScreen();

#endif // GAMEFUNC_H
