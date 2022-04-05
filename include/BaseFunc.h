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

//-----Window-----
const int SCREEN_WIDTH = 1120;
const int SCREEN_HEIGHT = 630;
const int RENDER_DRAW_COLOR = 0xff;
const std::string WINDOW_TITLE = "Banana Kong!";

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;


//-----Game-----

static const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

bool init();
bool loadMedia();
void close();

//----------End of Base Variable---------->

//----------Function---------->


#endif //BASE_FUNC_H_
