#include "include/GameObj.h"
#include "include/BaseFunc.h"
#include "include/BaseObj.h"
#include "include/GameFunc.h"


using namespace std;


BaseObject backgroundTexture[BACKGROUND_LAYERS_COUNT];


BaseObject gMonkeyWalking_Texture;
BaseObject gMonkeyRunning_Texture;


SDL_Rect gMonkeyWalking_Clips[MONKEY_WALKING_FRAME];
SDL_Rect gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME];


int main( int argc, char* args[] )
{
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            bool quit = false;

            SDL_Event e;

            int frame = 0;

            while (!quit)
            {
                while( SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                //clear
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );
                SDL_RenderClear(gRenderer);

                RenderScrollingBackground( backgroundTexture, gRenderer );

//                SDL_Rect* currentClip = &gMonkeyWalking_Clips[frame / 10];
//
//                gMonkeyWalking_Texture.render (gRenderer, 350, 480, 100, 120, currentClip );


                SDL_Rect* currentClip = &gMonkeyRunning_Clips[frame / 4];

                gMonkeyRunning_Texture.render (gRenderer, 350, 480, 100, 120, currentClip );

                SDL_RenderPresent(gRenderer);

                ++frame;

                if(frame / 4 >= MONKEY_WALKING_FRAME) frame = 0;

            }
        }
    }
    close();
    return 0;
}


bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create gWindow
        gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "gWindow could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL)
            {
                printf("gRenderer could not be created! SDL error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );

                int imgFlags = IMG_INIT_PNG;
                if( !(IMG_Init(imgFlags) & imgFlags) )
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = 0;
                }
            }
        }
    }
    return success;
}


bool loadMedia(){

    bool success = true;

    if(!gMonkeyWalking_Texture.loadFromFile("Material/Characters/Monkey/MonkeyWalk.png", gRenderer))
    {
        printf( "Failed to load monkeyWalk texture image!\n" );
        success = false;
    }
    else {
            gMonkeyWalking_Clips[0].x = 140 * 0;
            gMonkeyWalking_Clips[0].y = 0;
            gMonkeyWalking_Clips[0].h = 168;
            gMonkeyWalking_Clips[0].w = 140;

            gMonkeyWalking_Clips[1].x = 140 * 1;
            gMonkeyWalking_Clips[1].y = 0;
            gMonkeyWalking_Clips[1].h = 168;
            gMonkeyWalking_Clips[1].w = 140;

            gMonkeyWalking_Clips[2].x = 140 * 2;
            gMonkeyWalking_Clips[2].y = 0;
            gMonkeyWalking_Clips[2].h = 168;
            gMonkeyWalking_Clips[2].w = 140;

            gMonkeyWalking_Clips[3].x = 140 * 3;
            gMonkeyWalking_Clips[3].y = 0;
            gMonkeyWalking_Clips[3].h = 168;
            gMonkeyWalking_Clips[3].w = 140;

    }


    if(!gMonkeyRunning_Texture.loadFromFile("Material/Characters/Monkey/MonkeyRun.png", gRenderer))
    {
        printf( "Failed to load monkeyRun texture image!\n" );
        success = false;
    }
    else {
            gMonkeyRunning_Clips[0].x = 140 * 0;
            gMonkeyRunning_Clips[0].y = 0;
            gMonkeyRunning_Clips[0].h = 168;
            gMonkeyRunning_Clips[0].w = 140;

            gMonkeyRunning_Clips[1].x = 140 * 1;
            gMonkeyRunning_Clips[1].y = 0;
            gMonkeyRunning_Clips[1].h = 168;
            gMonkeyRunning_Clips[1].w = 140;

            gMonkeyRunning_Clips[2].x = 140 * 2;
            gMonkeyRunning_Clips[2].y = 0;
            gMonkeyRunning_Clips[2].h = 168;
            gMonkeyRunning_Clips[2].w = 140;

            gMonkeyRunning_Clips[3].x = 140 * 3;
            gMonkeyRunning_Clips[3].y = 0;
            gMonkeyRunning_Clips[3].h = 168;
            gMonkeyRunning_Clips[3].w = 140;

            gMonkeyRunning_Clips[4].x = 140 * 4;
            gMonkeyRunning_Clips[4].y = 0;
            gMonkeyRunning_Clips[4].h = 168;
            gMonkeyRunning_Clips[4].w = 140;

            gMonkeyRunning_Clips[5].x = 140 * 5;
            gMonkeyRunning_Clips[5].y = 0;
            gMonkeyRunning_Clips[5].h = 168;
            gMonkeyRunning_Clips[5].w = 140;

            gMonkeyRunning_Clips[6].x = 140 * 6;
            gMonkeyRunning_Clips[6].y = 0;
            gMonkeyRunning_Clips[6].h = 168;
            gMonkeyRunning_Clips[6].w = 140;

            gMonkeyRunning_Clips[7].x = 140 * 7;
            gMonkeyRunning_Clips[7].y = 0;
            gMonkeyRunning_Clips[7].h = 168;
            gMonkeyRunning_Clips[7].w = 140;

    }

    for(int i = 0; i < BACKGROUND_LAYERS_COUNT; ++i){
        if( !backgroundTexture[i].loadFromFile( BACKGROUND_LAYERS_PATH[i], gRenderer ) )
        {
            printf( "Failed to load background layer %d texture image!\n", i );
            success = false;
        }
    }
    return success;

}


void close()
{
    gMonkeyRunning_Texture.free();
    gMonkeyWalking_Texture.free();
    for(int i = 0; i < BACKGROUND_LAYERS_COUNT; ++i){
        backgroundTexture[i].free();
    }
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
}

