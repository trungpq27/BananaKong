#include "Background.h"

void RenderScrollingBackground(BaseObject (&backgroundTexture)[BACKGROUND_LAYERS_COUNT], SDL_Renderer* gRenderer, int MonkeyDash){

    for(int i = 0; i < BACKGROUND_LAYERS_COUNT; ++i){
        BACKGROUND_SCROLLING_OFFSET[i] -= BACKGROUND_LAYERS_SPEED[i];
        if( BACKGROUND_SCROLLING_OFFSET[i] <= -SCREEN_WIDTH )
        {
            BACKGROUND_SCROLLING_OFFSET[i] = 0;
        }
        if (MonkeyDash != NULL) BACKGROUND_SCROLLING_OFFSET[i] += MonkeyDash;
        backgroundTexture[i].render(gRenderer, BACKGROUND_SCROLLING_OFFSET[i], 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        backgroundTexture[i].render(gRenderer, BACKGROUND_SCROLLING_OFFSET[i] + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
}

void RenderScrollingGround(BaseObject &groundTexture, SDL_Renderer* gRenderer, int GROUND_SPEED, int MonkeyDash){

    GROUND_SCROLLING_OFFSET -= GROUND_SPEED;
    if( GROUND_SCROLLING_OFFSET <= -SCREEN_WIDTH )
    {
        GROUND_SCROLLING_OFFSET = 0;
    }
    if (MonkeyDash != NULL) GROUND_SCROLLING_OFFSET += MonkeyDash;
    groundTexture.render(gRenderer, GROUND_SCROLLING_OFFSET, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    groundTexture.render(gRenderer, GROUND_SCROLLING_OFFSET + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
