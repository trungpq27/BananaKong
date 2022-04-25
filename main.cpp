#define SDL_MAIN_HANDLED
#include "gMonkey.h"
#include "BaseFunc.h"
#include "BaseObj.h"
#include "Background.h"
#include "HigherPath.h"
#include "Obstacle.h"
#include "GameFunc.h"
#include "gText.h"
#include "Timer.h"
#include "gBanana.h"
#include "Button.h"


using namespace std;

//<----------Declare----------

//-----Sound-----
bool Death_Sound_Played = 0;
Mix_Music *gMusic = NULL;
Mix_Chunk *gBananaGet_Sound = NULL;
Mix_Chunk *gMonkeyJump_Sound = NULL;
Mix_Chunk *gClick_Sound = NULL;
Mix_Chunk *Hover_Sound = NULL;
Mix_Chunk *Death_Sound = NULL;
Mix_Chunk *SeeYa = NULL;

//-----TimerAndText-----

TTF_Font *gFont = NULL;
TTF_Font *gBorderFont = NULL;

TTF_Font *gDeathFont = NULL;
TTF_Font *gDeathBorderFont = NULL;

gText gTextTexture;
Timer gTimer;

//-----Background-----
BaseObject Paused_Text;
BaseObject DeathScreen;
BaseObject StartBackground_Texture;
BaseObject backgroundTexture[BACKGROUND_LAYERS_COUNT];
BaseObject groundTexture;

//-----Button-----
Button StartButton(MENU_BUTTON_ID);
Button ExitButton(MENU_BUTTON_ID);
Button AgainButton(MENU_BUTTON_ID);

Button PlayButton(PAUSE_BUTTON_ID);
Button PauseButton(PAUSE_BUTTON_ID);

//-----ScoreBoard-----
BaseObject ScoreBoard;

//-----gMonkey-----
int gMonkeyState = STATE_RUN;
int JumpBreak = 0;
int JumpTo_Pos = gMonkey_JumpTo_Y1;
int FallTo_Pos = gMonkey_Stable_PosY;
pair <int, int> gMonkey_Pos = {gMonkey_Stable_PosX, gMonkey_Stable_PosY};

int MONKEY_RUNNING_FRAME = 0;
int MONKEY_JUMPING_SPEED;
double MONKEY_RUNNING_SPEED = BASE_MONKEY_SPEED;
int MONKEY_ANIMATION_SPEED = MONKEY_RUNNING_SPEED*0.75;

gMonkey gMonkeyRunning_Texture;
gMonkey gMonkeyJumping_Texture;
gMonkey gMonkeyFallNPR_Texture;
gMonkey gMonkeyFallPARA_Texture;

SDL_Rect gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME_COUNT];

//-----HigherPath-----
HigherPath AirPath1_Texture;
HigherPath AirPath2_Texture;
HigherPath UpPath1_Texture;
HigherPath UpPath2_Texture;

//-----Obstacle-----
Obstacle StonePig_Texture;
Obstacle Tent_Texture;

//-----gBanana-----
gBanana gBanana_Texture;

//----------End of Declare---------->


//<----------Main----------
int main( int argc, char* args[] )
{
    if( !init() ) printf( "Failed to initialize!\n" );
    else
    {
        if( !loadMedia() )  printf( "Failed to load media!\n" );

        else
        {
            Mix_PlayMusic( gMusic, -1 );

            bool menu = true;
            bool play = false;
            StartButton.setPos(390, 200);
            ExitButton.setPos(390, 380);
            SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );

            while(menu)
            {
                SDL_Event e_mouse;
				while (SDL_PollEvent(&e_mouse) != 0)
				{
					if (e_mouse.type == SDL_QUIT) {
                            Exit_Sound(SeeYa);
                            menu = false;
					}

					bool quit_game = false;

                    StartButton.handleEvent(&e_mouse, menu, play, Hover_Sound, gClick_Sound);
                    ExitButton.handleEvent(&e_mouse, menu, quit_game, Hover_Sound, gClick_Sound);

                    if (quit_game == true){
                        Exit_Sound(SeeYa);
                        close();
                        return 0;
                    }
                }
                SDL_RenderClear(gRenderer);

                RenderScrollingBackground( backgroundTexture, gRenderer );
                RenderScrollingGround( groundTexture, gRenderer, MONKEY_RUNNING_SPEED);

                StartBackground_Texture.render(gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

                SDL_Rect* currentClip = NULL;
                currentClip = &gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED];
                ++MONKEY_RUNNING_FRAME;
                if (MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED >= MONKEY_RUNNING_FRAME_COUNT) MONKEY_RUNNING_FRAME = 0;
                gMonkeyRunning_Texture.render(gRenderer, currentClip);

                StartButton.render(gRenderer);
                ExitButton.render(gRenderer);

                SDL_RenderPresent(gRenderer);
            }

            while(play){

                //-----SoundInit-----
                if(Death_Sound_Played){
                    Mix_HaltChannel(-1);
                    Death_Sound_Played = false;
                }
                if (Mix_PlayingMusic() == 0) Mix_PlayMusic( gMusic, -1 );
                else if( Mix_PausedMusic() == 1 ) Mix_ResumeMusic();

                //-----gMonkeyInit-----
                gMonkeyState = STATE_RUN;
                JumpBreak = 0;
                JumpTo_Pos = gMonkey_JumpTo_Y1;
                FallTo_Pos = gMonkey_Stable_PosY;
                gMonkey_Pos = {gMonkey_Stable_PosX, gMonkey_Stable_PosY};
                MONKEY_RUNNING_SPEED = BASE_MONKEY_SPEED;
                MONKEY_RUNNING_FRAME = 0;

                //-----HigherPathInit-----
                pair<double, double> PathPosX_Carry[HIGHER_PATH_COUNT+1];
                AirPath1_Texture.init(AIR_PATH1_ID, PathPosX_Carry);
                AirPath2_Texture.init(AIR_PATH2_ID, PathPosX_Carry);
                UpPath1_Texture.init(UP_PATH1_ID, PathPosX_Carry);
                UpPath2_Texture.init(UP_PATH2_ID, PathPosX_Carry);

                //-----ObstacleInit-----
                StonePig_Texture.init(STONE_PIG_ID, PathPosX_Carry);
                Tent_Texture.init(TENT_ID, PathPosX_Carry);

                //-----gBananaInit-----
                list<pair<double, int>> BananaPos;
                gBanana_Texture.init(BananaPos);

                //-----TimerScoreInit-----
                string DeathMessage = "YOU LOSE!";
                gTimer.start();
                long gRunDistance = 0;
                int Banana_Score = 0;

                //-----DeathScreen Button-----;
                AgainButton.setPos(200, 400);
                ExitButton.setPos(570, 400);

                PlayButton.setPos(5,0);
                PauseButton.setPos(5,0);

                //-----GameStateInit-----
                bool game_over = false;
                bool game_paused = false;
                bool quit = false;
                SDL_Event e;

                while (!quit) {
                    while( SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) quit = true, play = false;

                        PlayButton.handleEvent(&e, quit, game_paused, Hover_Sound, gClick_Sound);
                    }

                    //SDL_Delay(5); //delay cho do lag

                    MONKEY_ANIMATION_SPEED = MONKEY_RUNNING_SPEED*0.75;
                    MONKEY_JUMPING_SPEED = MONKEY_RUNNING_SPEED*2.5;

                    //-----Clear Render-----
                    SDL_RenderClear(gRenderer);

                    //-----Scrolling Background-----
                    RenderScrollingBackground( backgroundTexture, gRenderer );
                    RenderScrollingGround( groundTexture, gRenderer, MONKEY_RUNNING_SPEED);

                    //-----Higher Path-----
                    UpPath1_Texture.Move(MONKEY_RUNNING_SPEED, PathPosX_Carry);
                    UpPath1_Texture.render(gRenderer, UP_PATH1_WIDTH, UP_PATH1_HEIGHT);

                    UpPath2_Texture.Move(MONKEY_RUNNING_SPEED, PathPosX_Carry);
                    UpPath2_Texture.render(gRenderer, UP_PATH2_WIDTH, UP_PATH2_HEIGHT);

                    AirPath1_Texture.Move(MONKEY_RUNNING_SPEED, PathPosX_Carry);
                    AirPath1_Texture.render(gRenderer, AIR_PATH1_WIDTH, AIR_PATH1_HEIGHT);

                    AirPath2_Texture.Move(MONKEY_RUNNING_SPEED, PathPosX_Carry);
                    AirPath2_Texture.render(gRenderer, AIR_PATH2_WIDTH, AIR_PATH2_HEIGHT);

                    //-----Obstacle-----
                    StonePig_Texture.Move(MONKEY_RUNNING_SPEED, PathPosX_Carry);
                    StonePig_Texture.render(gRenderer, STONE_PIG_WIDTH, STONE_PIG_HEIGHT);
                    StonePig_Texture.Handle_Monkey(gMonkey_Pos, game_over, gMonkeyState);

                    Tent_Texture.Move(MONKEY_RUNNING_SPEED, PathPosX_Carry);
                    Tent_Texture.render(gRenderer, TENT_WIDTH, TENT_HEIGHT);
                    Tent_Texture.Handle_Monkey(gMonkey_Pos, game_over, gMonkeyState);

                    //-----gBanana-----
                    gBanana_Texture.render(gRenderer, BANANA_WIDTH, BANANA_HEIGHT, MONKEY_RUNNING_SPEED, BananaPos);
                    gBanana_Texture.Handle_Monkey(gMonkey_Pos, BananaPos, Banana_Score, gBananaGet_Sound);

                    //-----Running Monkey-----
                    gMonkeyHandleHigherPath(gMonkeyState, gMonkey_Pos, PathPosX_Carry, FallTo_Pos, MONKEY_JUMPING_SPEED, JumpBreak);

                    gMonkeyHandleMoving(gRenderer, JumpBreak, gMonkeyState, gMonkey_Pos, JumpTo_Pos, FallTo_Pos,
                                        gMonkeyRunning_Texture,gMonkeyRunning_Clips, gMonkeyJumping_Texture, gMonkeyFallNPR_Texture, gMonkeyFallPARA_Texture,
                                        MONKEY_RUNNING_SPEED, MONKEY_RUNNING_FRAME, MONKEY_ANIMATION_SPEED, MONKEY_JUMPING_SPEED, gTimer, gMonkeyJump_Sound);

                    //-----Score-----
                    gRunDistance += MONKEY_RUNNING_SPEED;
                    string scoreNow = longLongToString(gRunDistance/80) + " m";
                    string bananaScoreNow = longLongToString(Banana_Score) + " Banana";
                    if (Banana_Score >= 2) bananaScoreNow += 's';

                    gTextTexture.loadFromRenderedText( scoreNow, ScoreBorderColor, gBorderFont, gRenderer);
                    gTextTexture.render( gRenderer, 10, 30 );

                    gTextTexture.loadFromRenderedText( scoreNow, ScoreColor, gFont, gRenderer);
                    gTextTexture.render( gRenderer, 12, 29 );

                    gTextTexture.loadFromRenderedText( bananaScoreNow, ScoreBorderColor, gBorderFont, gRenderer);
                    gTextTexture.render( gRenderer, 10, 60 );

                    gTextTexture.loadFromRenderedText( bananaScoreNow, ScoreColor, gFont, gRenderer);
                    gTextTexture.render( gRenderer, 12, 59 );

                    int BestDistance = gRunDistance/80, BestBanana = Banana_Score;
                    UpdateHighScore(BestDistance, BestBanana, DeathMessage);

                    //cout << gTimer.getTicks() << "\n"; //debug only

                    //-----PlayPause-----

                    PlayButton.render(gRenderer);
                    //-----RenderPresent-----
                    SDL_RenderPresent(gRenderer);

                    //-----Handle Pause/Death-----
                    if (game_over || game_paused) DeathScreenShot(DeathScreen, gRenderer);

                    while (game_over || game_paused)
                    {
                        if(game_paused) Mix_PauseMusic();
                        if(game_over && !Death_Sound_Played){
                            Mix_HaltMusic();
                            Mix_PlayChannel(-1, Death_Sound, 0);
                            Death_Sound_Played = 1;
                        }
                        HandleGameOver(game_over, game_paused, play, quit, gTimer, AgainButton, ExitButton, PauseButton, Hover_Sound, gClick_Sound, SeeYa);

                        //-----Score Board-----
                        SDL_RenderClear(gRenderer);

                        scoreNow = "Distance:  " + longLongToString(gRunDistance/80) + " (Best " + longLongToString(BestDistance) + ")";
                        bananaScoreNow = "Banana:  " + longLongToString(Banana_Score) + " (Best " + longLongToString(BestBanana) + ")";

                        HandleDeathScreen (gRenderer, DeathScreen, game_over, ScoreBoard, Paused_Text, gTextTexture,
                                           gDeathFont, gDeathBorderFont, AgainButton, ExitButton, PauseButton, scoreNow,
                                           bananaScoreNow, DeathMessage);

                        SDL_RenderPresent(gRenderer);
                    }

                }

            }
        }
    }
    close();
    return 0;
}
//----------End of Main---------->

//<----------Base Function----------
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

    //-----gfont-----
    gFont = TTF_OpenFont( "Material/Fonts/UVNVan.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	gBorderFont = TTF_OpenFont( "Material/Fonts/UVNVan.ttf", 28 );
	if( gBorderFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	gDeathFont = TTF_OpenFont( "Material/Fonts/Nueva.ttf", 40 );
	if( gDeathFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	gDeathBorderFont = TTF_OpenFont( "Material/Fonts/Nueva.ttf", 40 );
	if( gDeathBorderFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else TTF_SetFontOutline(gDeathBorderFont, 1);

	//-----ScoreBoard-----
	if(!ScoreBoard.loadFromFile("Material/Others/ScoreBoard.png", gRenderer)){
        printf( "Failed to load ScoreBoard texture image!\n" );
        success = false;
    }

    //-----gMonkey-----
    if(!gMonkeyJumping_Texture.loadFromFile("Material/Characters/Monkey/MonkeyJump.png", gRenderer)){
        printf( "Failed to load monkeyJump texture image!\n" );
        success = false;
    }

    if(!gMonkeyFallNPR_Texture.loadFromFile("Material/Characters/Monkey/MonkeyFall_NoPara.png", gRenderer)){
        printf( "Failed to load monkeyFallNoPara texture image!\n" );
        success = false;
    }

    if(!gMonkeyFallPARA_Texture.loadFromFile("Material/Characters/Monkey/MonkeyFall_Para.png", gRenderer)){
        printf( "Failed to load monkeyFallPara texture image!\n" );
        success = false;
    }

    if(!gMonkeyRunning_Texture.loadFromFile("Material/Characters/Monkey/MonkeyRun.png", gRenderer)){
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
    //-----gBanana-----
    if(!gBanana_Texture.loadFromFile("Material/Characters/Banana/Banana.png", gRenderer)){
        printf( "Failed to load Banana texture image!\n" );
        success = false;
    }

    //-----Background-----
    if (!groundTexture.loadFromFile("Material/Background/Ground.png", gRenderer)){
        printf( "Failed to load Ground texture image!\n" );
        success = false;
    }

    for(int i = 0; i < BACKGROUND_LAYERS_COUNT; ++i){
        if( !backgroundTexture[i].loadFromFile( BACKGROUND_LAYERS_PATH[i], gRenderer ) ){
            printf( "Failed to load background layer %d texture image!\n", i );
            success = false;
        }
    }

    if( !StartBackground_Texture.loadFromFile( "Material/Background/Title.png", gRenderer ) ){
        printf( "Failed to load StartBackground layer %d texture image!\n");
        success = false;
    }
    if( !Paused_Text.loadFromFile( "Material/Menu/PlayPause/Paused.png", gRenderer ) ){
        printf( "Failed to load Paused_Text layer %d texture image!\n");
        success = false;
    }

    //-----Button-----
    if( !StartButton.loadFromFile( "Material/Menu/Button/Start.png", gRenderer ) ){
        printf( "Failed to load StartButton layer %d texture image!\n");
        success = false;
    }

    if( !ExitButton.loadFromFile( "Material/Menu/Button/Exit.png", gRenderer ) ){
        printf( "Failed to load ExitButton layer %d texture image!\n");
        success = false;
    }

    if( !AgainButton.loadFromFile( "Material/Menu/Button/Again.png", gRenderer ) ){
        printf( "Failed to load AgainButton layer %d texture image!\n");
        success = false;
    }


    if( !PlayButton.loadFromFile( "Material/Menu/PlayPause/Play.png", gRenderer ) ){
        printf( "Failed to load PlayButton layer %d texture image!\n");
        success = false;
    }

    if( !PauseButton.loadFromFile( "Material/Menu/PlayPause/Pause.png", gRenderer ) ){
        printf( "Failed to load PauseButton layer %d texture image!\n");
        success = false;
    }

    //-----HigherPath-----
    if (!AirPath1_Texture.loadFromFile("Material/HigherPath/AirPath1.png", gRenderer)){
        printf( "Failed to load Ground AirPath1 image!\n" );
        success = false;
    }
    if (!AirPath2_Texture.loadFromFile("Material/HigherPath/AirPath2.png", gRenderer)){
        printf( "Failed to load Ground AirPath2 image!\n" );
        success = false;
    }
    if (!UpPath1_Texture.loadFromFile("Material/HigherPath/UpPath1.png", gRenderer)){
        printf( "Failed to load Ground UpPath1 image!\n" );
        success = false;
    }
    if (!UpPath2_Texture.loadFromFile("Material/HigherPath/UpPath2.png", gRenderer)){
        printf( "Failed to load Ground UpPath2 image!\n" );
        success = false;
    }

    //-----Obstacle-----
    if (!StonePig_Texture.loadFromFile("Material/Obstacle/StonePig.png", gRenderer)){
        printf( "Failed to load Ground StonePig image!\n" );
        success = false;
    }
    if (!Tent_Texture.loadFromFile("Material/Obstacle/Tent.png", gRenderer)){
        printf( "Failed to load Ground Tent image!\n" );
        success = false;
    }

    //Load music
    gMusic = Mix_LoadMUS( "Material/Sound/MainBgm.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gBananaGet_Sound = Mix_LoadWAV( "Material/Sound/BananaGet.wav" );
    if( gBananaGet_Sound == NULL )
    {
        printf( "Failed to load BananaGet effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gMonkeyJump_Sound = Mix_LoadWAV( "Material/Sound/MonkeyJump.wav" );
    if( gBananaGet_Sound == NULL )
    {
        printf( "Failed to load MonkeyJump effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gClick_Sound = Mix_LoadWAV( "Material/Sound/MouseClick.wav" );
    if( gClick_Sound == NULL )
    {
        printf( "Failed to load MouseClick effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    Hover_Sound = Mix_LoadWAV( "Material/Sound/ButtonHover.wav" );
    if( Hover_Sound == NULL )
    {
        printf( "Failed to load ButtonHover effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    Death_Sound = Mix_LoadWAV( "Material/Sound/Death.wav" );
    if( Death_Sound == NULL )
    {
        printf( "Failed to load Death effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    SeeYa = Mix_LoadWAV( "Material/Sound/seeya.wav" );
    if( SeeYa == NULL )
    {
        printf( "Failed to load SeeYa effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;

}

void close()
{
    //-----gText-----
    gTextTexture.free();

    //-----gMonkey-----
    gMonkeyRunning_Texture.free();
    gMonkeyJumping_Texture.free();
    gMonkeyFallNPR_Texture.free();
    gMonkeyFallPARA_Texture.free();
    StartBackground_Texture.free();
    DeathScreen.free();
    Paused_Text.free();


    //-----Backgorund-----
    groundTexture.free();
    for(int i = 0; i < BACKGROUND_LAYERS_COUNT; ++i){
        backgroundTexture[i].free();
    }

    //-----HigherPath-----
    AirPath1_Texture.free();
    AirPath2_Texture.free();
    UpPath1_Texture.free();
    UpPath2_Texture.free();

    //-----Obstacle-----
    StonePig_Texture.free();
    Tent_Texture.free();

    //-----gBanana-----
    gBanana_Texture.free();

    //-----Button-----
    StartButton.free();
    ExitButton.free();
    AgainButton.free();
    PlayButton.free();
    PauseButton.free();

    //-----gTimer/gText-----
    gTimer.stop();
    gTextTexture.free();

    //-----Music-----
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk( gBananaGet_Sound );
    Mix_FreeChunk( gMonkeyJump_Sound );
    Mix_FreeChunk( gClick_Sound );
    Mix_FreeChunk( Hover_Sound );
    Mix_FreeChunk( Death_Sound );
    gMusic = NULL;
    gBananaGet_Sound = NULL;
    gMonkeyJump_Sound = NULL;
    gClick_Sound = NULL;
    Hover_Sound = NULL;
    Death_Sound = NULL;

    //-----Window-----
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;
    gWindow = NULL;

    //-----SDL-----
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}
//----------End of Base Function---------->

