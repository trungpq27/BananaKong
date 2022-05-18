#ifndef BASE_FUNC_H_
#define BASE_FUNC_H_

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

//<----------Base Variable----------

extern const Uint8* currentKeyStates;

//---Screen Level ID---
const int POSY_GROUND_ID = 0;
const int POSY_UP_ID = 1;
const int POSY_AIR_ID = 2;
const int SCREEN_LEVEL_COUNT = 3;


//-----Window-----
const int SCREEN_WIDTH = 1120;
const int SCREEN_HEIGHT = 630;
const int RENDER_DRAW_COLOR = 0xff;
const std::string WINDOW_TITLE = "Banana Kong!";

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;


//-----Game-----
extern bool init();
extern bool loadMedia();
extern void close();

//----------End of Base Variable---------->

//----------Function---------->


#endif //BASE_FUNC_H_
