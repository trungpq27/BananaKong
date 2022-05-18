#include "Background.h"

//----------Declare----------
BaseObject backgroundTexture[BACKGROUND_LAYERS_COUNT];
BaseObject groundTexture;

//----------Function----------

void RenderScrollingBackground(int MonkeyDash){

    for(int i = 0; i < BACKGROUND_LAYERS_COUNT; ++i){
        BACKGROUND_SCROLLING_OFFSET[i] -= BACKGROUND_LAYERS_SPEED[i];
        if( BACKGROUND_SCROLLING_OFFSET[i] <= -SCREEN_WIDTH )
        {
            BACKGROUND_SCROLLING_OFFSET[i] = 0;
        }
        if (MonkeyDash != NULL) BACKGROUND_SCROLLING_OFFSET[i] += MonkeyDash;
        backgroundTexture[i].render(BACKGROUND_SCROLLING_OFFSET[i], 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        backgroundTexture[i].render(BACKGROUND_SCROLLING_OFFSET[i] + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
}

void RenderScrollingGround(int MonkeyDash){

    GROUND_SCROLLING_OFFSET -= MONKEY_RUNNING_SPEED;
    if( GROUND_SCROLLING_OFFSET <= -SCREEN_WIDTH )
    {
        GROUND_SCROLLING_OFFSET = 0;
    }
    if (MonkeyDash != NULL) GROUND_SCROLLING_OFFSET += MonkeyDash;
    groundTexture.render(GROUND_SCROLLING_OFFSET, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    groundTexture.render(GROUND_SCROLLING_OFFSET + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

//----------Load Media----------
bool isLoadBackgroundOK(){
    bool success = true;
    if (!groundTexture.loadFromFile("Material/Background/Ground.png")){
        printf( "Failed to load Ground texture image!\n" );
        success = false;
    }

    for(int i = 0; i < BACKGROUND_LAYERS_COUNT; ++i){
        if( !backgroundTexture[i].loadFromFile( BACKGROUND_LAYERS_PATH[i] ) ){
            printf( "Failed to load background layer %d texture image!\n", i );
            success = false;
        }
    }
    return success;
}

void closeBackground(){
    groundTexture.free();
    for(int i = 0; i < BACKGROUND_LAYERS_COUNT; ++i){
        backgroundTexture[i].free();
    }
}
