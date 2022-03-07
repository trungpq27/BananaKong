#include "GameFunc.h"


bool init(){

    bool success = 0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }

    else {
        gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer = NULL){
                printf("Renderer could not be created! SDL error: %s\n", SDL_GetError() );
                success = false;
            }
            else{
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)){
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }

        }
    }
    return success;
}





void close()
{
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    gEvent = NULL;

    IMG_Quit();
    SDL_Quit();
}
