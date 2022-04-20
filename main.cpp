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


using namespace std;

//<----------Declare----------

Timer gTimer;

TTF_Font *gFont = NULL;
TTF_Font *gBorderFont = NULL;
long long gRunDistance;

//-----Background-----

int gMonkeyState = STATE_RUN;

int MONKEY_RUNNING_FRAME = 0;

double MONKEY_RUNNING_SPEED = BASE_MONKEY_SPEED;
int MONKEY_ANIMATION_SPEED;
int MONKEY_JUMPING_SPEED;

BaseObject backgroundTexture[BACKGROUND_LAYERS_COUNT];
BaseObject groundTexture;
gText gTextTexture;

//-----ScoreBoard-----
BaseObject ScoreBoard;

//-----gMonkey-----
int JumpTo_Pos = gMonkey_JumpTo_Y1;
int FallTo_Pos = gMonkey_Stable_PosY;

int JumpBreak = 0;

gMonkey gMonkeyWalking_Texture;
gMonkey gMonkeyRunning_Texture;
gMonkey gMonkeyJumping_Texture;
gMonkey gMonkeyFallNPR_Texture;
gMonkey gMonkeyFallPARA_Texture;

SDL_Rect gMonkeyWalking_Clips[MONKEY_WALKING_FRAME_COUNT];
SDL_Rect gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME_COUNT];

pair <int, int> gMonkey_Pos = {gMonkey_Stable_PosX, gMonkey_Stable_PosY};

//-----HigherPath-----
pair<double, double> PathPosX_Carry[HIGHER_PATH_COUNT+1];
HigherPath AirPath1_Texture(AIR_PATH1_ID, PathPosX_Carry);
HigherPath AirPath2_Texture(AIR_PATH2_ID, PathPosX_Carry);
HigherPath UpPath1_Texture(UP_PATH1_ID, PathPosX_Carry);
HigherPath UpPath2_Texture(UP_PATH2_ID, PathPosX_Carry);

//-----Obstacle-----
Obstacle StonePig_Texture(STONE_PIG_ID, PathPosX_Carry);
Obstacle Tent_Texture(TENT_ID, PathPosX_Carry);

//-----gBanana-----
list<pair<double, int>> BananaPos;
gBanana gBanana_Texture(BananaPos);
int Banana_Score = 0;


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
            bool quit = false;
            SDL_Event e;
            int frame = 0;

            //-----set Timer-----
            gTimer.start();

            while (!quit) {
                while( SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                SDL_Delay(5);

                MONKEY_ANIMATION_SPEED = MONKEY_RUNNING_SPEED*0.75;
                MONKEY_JUMPING_SPEED = MONKEY_RUNNING_SPEED*2.5;

                //-----Clear Render-----
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );
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

                Tent_Texture.Move(MONKEY_RUNNING_SPEED, PathPosX_Carry);
                Tent_Texture.render(gRenderer, TENT_WIDTH, TENT_HEIGHT);

                //-----gBanana-----
                gBanana_Texture.render(gRenderer, BANANA_WIDTH, BANANA_HEIGHT, MONKEY_RUNNING_SPEED, BananaPos);
                gBanana_Texture.Handle_Monkey(gMonkey_Pos, BananaPos, Banana_Score);

                //-----Running Monkey-----
                gMonkeyHandleHigherPath(gMonkeyState, gMonkey_Pos, PathPosX_Carry, FallTo_Pos, MONKEY_JUMPING_SPEED, JumpBreak);
                gMonkeyHandleMoving();


                //-----Score Board-----
                //ScoreBoard.render(gRenderer, 3, 4, SCORE_BOARD_WIDTH, SCORE_BOARD_HEIGHT);

                //-----Score-----
                gRunDistance += MONKEY_RUNNING_SPEED;
                string scoreNow = longLongToString(gRunDistance/80) + " m";
                string bananaScoreNow = longLongToString(Banana_Score) + " Bananas";

                gTextTexture.loadFromRenderedText( scoreNow, ScoreBorderColor, gBorderFont, gRenderer);
                gTextTexture.render( gRenderer, 10, 30 );

                gTextTexture.loadFromRenderedText( scoreNow, ScoreColor, gFont, gRenderer);
                gTextTexture.render( gRenderer, 12, 29 );

                gTextTexture.loadFromRenderedText( bananaScoreNow, ScoreBorderColor, gBorderFont, gRenderer);
                gTextTexture.render( gRenderer, 10, 60 );

                gTextTexture.loadFromRenderedText( bananaScoreNow, ScoreColor, gFont, gRenderer);
                gTextTexture.render( gRenderer, 12, 59 );

                SDL_RenderPresent(gRenderer);

            }

        }
    }
    close();
    return 0;
}
//----------End of Main---------->


//----------Function---------->
void gMonkeyHandleMoving(){
    //cout << gMonkeyState << " " << gMonkey_Pos.second << " " << gMonkey_X1_PosY << " " << FallTo_Pos << "\n";  //debug only
    //cout << JumpBreak << "\n";  //debug only

    SDL_Rect* currentClip = NULL;

    if(gMonkeyState == STATE_RUN){
        JumpBreak += MONKEY_RUNNING_SPEED;
        setMonkeyPos(gMonkeyRunning_Texture, gMonkey_Pos);
        if(currentKeyStates[ SDL_SCANCODE_DOWN ]){
                gMonkey_Pos.second += MONKEY_JUMPING_SPEED;
                gMonkeyState = STATE_FALLNPR;
        }
        if(currentKeyStates[ SDL_SCANCODE_UP ] && JumpBreak >= BreakDistance){
            JumpTo_Pos = gMonkey_JumpTo_Y1;
            if (gMonkey_Pos.second == gMonkey_X1_PosY) JumpTo_Pos = gMonkey_JumpTo_Y2;
            if (gMonkey_Pos.second == gMonkey_X2_PosY) JumpTo_Pos = 0;
            gMonkeyState = STATE_JUMP;
        }

        else {
            currentClip = &gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED];
            ++MONKEY_RUNNING_FRAME;
            if (MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED >= MONKEY_RUNNING_FRAME_COUNT) MONKEY_RUNNING_FRAME = 0;
            gMonkeyRunning_Texture.render(gRenderer, currentClip);
        }
    }


    if(gMonkeyState == STATE_JUMP){
        setMonkeyPos(gMonkeyJumping_Texture, gMonkey_Pos);
        if(currentKeyStates[ SDL_SCANCODE_DOWN ]) gMonkeyState = STATE_FALLNPR;
        else{

            if(gMonkey_Pos.second > JumpTo_Pos){
                gMonkeyJumping_Texture.setPosY(gMonkeyJumping_Texture.getPosY()-MONKEY_JUMPING_SPEED);
                gMonkey_Pos.second -= MONKEY_JUMPING_SPEED;
                gMonkeyJumping_Texture.render(gRenderer, currentClip);
            }
            else {
                if (!currentKeyStates[ SDL_SCANCODE_UP ]) gMonkeyState = STATE_FALLNPR;
                else gMonkeyState = STATE_FALLPARA;
            }
        }
    }


    if(gMonkeyState == STATE_FALLNPR){
        setMonkeyPos(gMonkeyFallNPR_Texture, gMonkey_Pos);
        if(gMonkey_Pos.second < FallTo_Pos){

            if (currentKeyStates[ SDL_SCANCODE_UP ]) gMonkeyState = STATE_FALLPARA;

            else{
                gMonkeyFallNPR_Texture.setPosY(gMonkeyFallNPR_Texture.getPosY()+MONKEY_JUMPING_SPEED);
                gMonkey_Pos.second += MONKEY_JUMPING_SPEED;
                gMonkeyFallNPR_Texture.render(gRenderer, currentClip);
            }
        }
        else{
            gMonkeyState = STATE_RUN;
            gMonkey_Pos.second = FallTo_Pos;
        }
    }


    if(gMonkeyState == STATE_FALLPARA){
        setMonkeyPos(gMonkeyFallPARA_Texture, gMonkey_Pos);

        if(gMonkey_Pos.second < FallTo_Pos && !currentKeyStates[ SDL_SCANCODE_UP ]){
            gMonkeyState = STATE_FALLNPR;
        }

        if(gMonkey_Pos.second < FallTo_Pos){
            gMonkeyFallPARA_Texture.setPosY(gMonkeyFallPARA_Texture.getPosY()+MONKEY_RUNNING_SPEED);
            gMonkey_Pos.second += MONKEY_RUNNING_SPEED/2;
            gMonkeyFallPARA_Texture.render(gRenderer, currentClip);
        }
        else{
            gMonkeyState = STATE_RUN;
            JumpBreak = 0;
            gMonkey_Pos.second = FallTo_Pos;
        }
    }

    if (gMonkeyState == STATE_FALLNPR || gMonkeyState == STATE_FALLPARA){
            FallTo_Pos = gMonkey_Stable_PosY;
            if(gMonkey_Pos.second < gMonkey_X2_PosY) FallTo_Pos = gMonkey_X2_PosY;
            else if(gMonkey_Pos.second < gMonkey_X1_PosY) FallTo_Pos = gMonkey_X1_PosY;
    }

    MONKEY_RUNNING_SPEED = BASE_MONKEY_SPEED + (1.0*gTimer.getTicks()/50000);
}


//<----------Base Function----------
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
            }
        }
    }
    return success;
}


bool loadMedia(){

    bool success = true;

    //-----gfont-----
    gFont = TTF_OpenFont( fontPath.c_str(), 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	gBorderFont = TTF_OpenFont( fontPath.c_str(), 28 );
	if( gBorderFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
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

    if(!gMonkeyWalking_Texture.loadFromFile("Material/Characters/Monkey/MonkeyWalk.png", gRenderer)){
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

    return success;

}

void close()
{
    //-----gText-----
    gTextTexture.free();

    //-----gMonkey-----
    gMonkeyRunning_Texture.free();
    gMonkeyWalking_Texture.free();
    gMonkeyJumping_Texture.free();
    gMonkeyFallNPR_Texture.free();

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

    //Obstacle
    StonePig_Texture.free();
    Tent_Texture.free();

    //-----Window-----
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;
    gWindow = NULL;

    //-----SDL-----
    IMG_Quit();
    SDL_Quit();
}
//----------End of Base Function---------->

