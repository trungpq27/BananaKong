#ifndef BASE_FUNC_H_
#define BASE_FUNC_H_


#include <bits/stdc++.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int RENDER_DRAW_COLOR = 0xff;
const std::string WINDOW_TITLE = "Banana Kong!";


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event* gEvent = NULL;


#endif BASE_FUNC_H_
