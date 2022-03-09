#ifndef GAME_OBJ_H_
#define GAME_OBJ_H_


#include "BaseFunc.h"
#include "BaseObj.h"

const int MONKEY_WALKING_FRAME = 4;
const int MONKEY_RUNNING_FRAME = 8;
const int BACKGROUND_LAYERS_COUNT = 4;


const string BACKGROUND_LAYERS_PATH[BACKGROUND_LAYERS_COUNT] = {

    "Material/Background/Layer0.png",
    "Material/Background/Layer1.png",
    "Material/Background/Layer2.png",
    "Material/Background/Layer3.png",
};

static vector <double> SCROLLING_OFFSET = {0,0,0,0};
const double BACKGROUND_LAYERS_SPEED[BACKGROUND_LAYERS_COUNT] = {0, 0.5, 1, 1.5};


class gMonkey : public BaseObject{

public:
    gMonkey();

    ~gMonkey();

};

void RenderScrollingBackground( BaseObject (&backgroundTexture)[BACKGROUND_LAYERS_COUNT], SDL_Renderer* gRenderer );



#endif //GAME_OBJ_H_
