#include "GameObj.h"


gMonkey::gMonkey() : BaseObject(){};


gMonkey::~gMonkey(){
    BaseObject::free();
}

void RenderScrollingBackground( BaseObject (&backgroundTexture)[BACKGROUND_LAYERS_COUNT], SDL_Renderer* gRenderer ){
    for(int i = 0; i < BACKGROUND_LAYERS_COUNT; ++i){
        SCROLLING_OFFSET[i] -= BACKGROUND_LAYERS_SPEED[i];
        if( SCROLLING_OFFSET[i] < -SCREEN_WIDTH )
        {
            SCROLLING_OFFSET[i] = 0;
        }
        backgroundTexture[i].render(gRenderer, SCROLLING_OFFSET[i], 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        backgroundTexture[i].render(gRenderer, SCROLLING_OFFSET[i] + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
}
