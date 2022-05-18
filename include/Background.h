#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "BaseFunc.h"
#include "BaseObj.h"
#include "gMonkey.h"

//-----Declare-----
const int BACKGROUND_LAYERS_COUNT = 4;
static double GROUND_SCROLLING_OFFSET = 0;
static vector <double> BACKGROUND_SCROLLING_OFFSET = {0,0,0,0};
const double BACKGROUND_LAYERS_SPEED[BACKGROUND_LAYERS_COUNT] = {0, 0.5, 1, 1.5};
const string BACKGROUND_LAYERS_PATH[BACKGROUND_LAYERS_COUNT] = {
    "Material/Background/Layer0.png",
    "Material/Background/Layer1.png",
    "Material/Background/Layer2.png",
    "Material/Background/Layer3.png",
};

//-----Declare-----
extern BaseObject backgroundTexture[BACKGROUND_LAYERS_COUNT];
extern BaseObject groundTexture;

//-----Function-----
void RenderScrollingBackground (int MonkeyDash = NULL );
void RenderScrollingGround (int MonkeyDash = NULL );

//-----Load Media-----
extern bool isLoadBackgroundOK();
extern void closeBackground();


#endif // BACKGROUND_H
