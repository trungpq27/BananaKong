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
#include "Button.h"


const int BreakDistance = 50;

const int gMonkey_X1_PosY = HIGH_PATH_X1_POSY - MONKEY_HEIGHT + MONKEY_BORDER + UP_PATH_BORDER;
const int gMonkey_X2_PosY = HIGH_PATH_X2_POSY - MONKEY_HEIGHT + MONKEY_BORDER + AIR_PATH_BORDER;

void Exit_Sound(Mix_Chunk *SeeYa);

string longLongToString(long long x);

void gMonkeyHandleMoving();

void gMonkeyHandleHigherPath(int &gMonkeyState, pair<int, int> &gMonkey_Pos, pair<double, double> *PathPosX_Carry, int &FallTo_Pos, int MONKEY_JUMPING_SPEED, int &JumpBreak);

void gMonkeyHandleMoving(SDL_Renderer* gRenderer, int &JumpBreak, int &gMonkeyState, pair <int, int> &gMonkey_Pos, int &JumpTo_Pos, int &FallTo_Pos,
                         gMonkey &gMonkeyRunning_Texture, SDL_Rect *gMonkeyRunning_Clips, gMonkey &gMonkeyJumping_Texture, gMonkey &gMonkeyFallNPR_Texture,
                         gMonkey &gMonkeyFallPARA_Texture, double &MONKEY_RUNNING_SPEED, int &MONKEY_RUNNING_FRAME, int &MONKEY_ANIMATION_SPEED,
                         int &MONKEY_JUMPING_SPEED, Timer &gTimer, Mix_Chunk *gMonkeyJump_Sound);

void UpdateHighScore(int &BestDistance, int &BestBanana, string &DeathMessage);

void DeathScreenShot(BaseObject &DeathScreen, SDL_Renderer* gRenderer);

void HandleGameOver(bool &game_over, bool &game_paused, bool &play, bool &quit, Timer &gTimer, Button &AgainButton, Button &ExitButton, Button &PauseButton,
                    Mix_Chunk *Hover_Sound, Mix_Chunk *gClick_Sound, Mix_Chunk *SeeYa);

void HandleDeathScreen (SDL_Renderer* gRenderer, BaseObject &DeathScreen, bool &game_over, BaseObject &ScoreBoard, BaseObject &Paused_Text, gText &gTextTexture,
                        TTF_Font *gDeathFont, TTF_Font *gDeathBorderFont, Button &AgainButton, Button &ExitButton, Button &PauseButton, string scoreNow,
                        string bananaScoreNow, string DeathMessage);

#endif // GAMEFUNC_H
