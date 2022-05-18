#define SDL_MAIN_HANDLED
#include "GameFunc.h"


using namespace std;


//<----------Main----------
int main( int argc, char* args[] )
{
    srand(time(0));
    if( !init() ) printf( "Failed to initialize!\n" );
    else
    {
        backToMenu = true;

        if(!loadMedia())  printf( "Failed to load media!\n" );

        else while (backToMenu)
        {
            GameInitEverything();
            menu = true;
            play = false;

            while(menu) HandleMenu();

            while(play){

                GameInitEverything();

                SDL_Event e;
                while (!quit) {
                    while( SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT){
                                quit = true;
                                play = false;
                        }
                        PauseButton.handleEvent(&e, quit, game_paused);
                    }

                    gMonkeyHandleChangeSpeed();

                    //-----Clear Render-----
                    SDL_RenderClear(gRenderer);

                    //-----Scrolling Background-----
                    RenderScrollingBackground();
                    RenderScrollingGround();

                    //-----Higher Path-----
                    MoveAndRenderHigherPath();

                    //-----Banana-----
                    MoveAndGetBanana();

                    //-----Obstacle-----
                    MoveAndCollisionObstacle();

                    //-----Running Monkey-----
                    gMonkeyHandleHigherPath();
                    gMonkeyHandleMoving();

                    //-----Handle Pause/Death-----
                    if (game_over || game_paused) DeathScreenShot();

                    //-----Score-----
                    handleTopLeftScore();

                    //-----PlayPause-----
                    PauseButton.render();

                    //-----RenderPresent-----
                    SDL_RenderPresent(gRenderer);

                    while (game_over || game_paused)
                    {
                        if(game_paused) Mix_PauseMusic();
                        if(game_over && !Death_Sound_Played){
                            Mix_HaltMusic();
                            Mix_PlayChannel(-1, Death_Sound, 0);
                            Death_Sound_Played = 1;
                        }
                        HandleStopFunction();

                        //-----Score Board-----
                        HandleStopScreen();
                    }

                }

            }
        }
    }
    close();
    return 0;
}
//----------End of Main---------->


