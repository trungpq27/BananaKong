#include "BaseFunc.h"
#include "GameFunc.h"

const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


bool init()
{
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}
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
                    success = false;
                }
                if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia(){

    bool success = true;

    success = isLoadTextOK();

    success = isLoadMonkeyOK();

    success = isLoadBananaOK();

    success = isLoadBackgroundOK();

    success = isLoadBaseObjectOK();

    success = isLoadButtonOK();

    success = isLoadHigherPathOK();

    success = isLoadObstacleOK();

    success = isLoadSoundOK();

    return success;

}

void close()
{
    closeText();

    closeTimer();

    closeMonkey();

    closeBackground();

    closeBaseObject();

    closeHigherPath();

    closeObstacle();

    closeBanana();

    closeButton();

    closeSound();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;
    gWindow = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();

    exit(0);
}
