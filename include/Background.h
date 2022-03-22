#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "BaseFunc.h"
#include "BaseObj.h"

//-----Declare-----
const int BACKGROUND_LAYERS_COUNT = 4;
static int GROUND_SCROLLING_OFFSET = 0;
static vector <double> BACKGROUND_SCROLLING_OFFSET = {0,0,0,0};
const double BACKGROUND_LAYERS_SPEED[BACKGROUND_LAYERS_COUNT] = {0, 0.5, 1, 1.5};
const string BACKGROUND_LAYERS_PATH[BACKGROUND_LAYERS_COUNT] = {
    "Material/Background/Layer0.png",
    "Material/Background/Layer1.png",
    "Material/Background/Layer2.png",
    "Material/Background/Layer3.png",
};


//-----Function-----
void RenderScrollingBackground ( BaseObject (&backgroundTexture)[BACKGROUND_LAYERS_COUNT], SDL_Renderer* gRenderer, int MonkeyDash = NULL );
void RenderScrollingGround ( BaseObject &groundTexture, SDL_Renderer* gRenderer, int GROUND_SPEED, int MonkeyDash = NULL );


#endif // BACKGROUND_H
