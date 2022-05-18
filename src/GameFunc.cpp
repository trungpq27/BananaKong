#include "GameFunc.h"

//----------Declare----------
bool backToMenu = true;
bool menu = true;
bool play = false;
bool quit_game = false;
bool game_over = false;
bool game_paused = false;
bool quit = false;
bool exit_game = false;


//----------Function----------
string longLongToString(long long x){
    stringstream ss;
    ss << x;
    string str = ss.str();
    return str;
}

void GameInitEverything(){

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
    jumpToPos = 0;
    gMonkeyPos = {MONKEY_STABLE_POSX, MONKEY_STABLE_POSY};
    MONKEY_RUNNING_SPEED = BASE_MONKEY_SPEED;
    MONKEY_RUNNING_FRAME = 0;

    //-----HigherPathInit-----
    AirPath1_Texture.init(AIR_PATH1_ID);
    AirPath2_Texture.init(AIR_PATH2_ID);
    UpPath1_Texture.init(UP_PATH1_ID);
    UpPath2_Texture.init(UP_PATH2_ID);

    //-----ObstacleInit-----
    StonePig_Texture.init(STONE_PIG_ID);
    Tent_Texture.init(TENT_ID);

    //-----gBananaInit-----
    while(!BananaPos.empty()) BananaPos.pop_front();
    gBanana_Texture.init();

    //-----TimerScoreInit-----
    DeathMessage = "YOU LOSE!";
    gTimer.start();
    gRunDistance = 0;
    Banana_Score = 0;

    //-----gButton Init-----
    StartButton.setSize(START_BUTTON_WIDTH, START_BUTTON_HEIGHT);
    StartButton.setPos((SCREEN_WIDTH - START_BUTTON_WIDTH)/2, 200);

    ExitButton.setSize(START_BUTTON_WIDTH, START_BUTTON_HEIGHT);
    ExitButton.setPos((SCREEN_WIDTH - START_BUTTON_WIDTH)/2, 380);

    AgainButton.setSize(START_BUTTON_WIDTH, START_BUTTON_HEIGHT);
    AgainButton.setPos(200, 400);

    PauseButton.setSize(SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
    PauseButton.setPos(5,5);

    PlayButton.setSize(ROUND_BUTTON_SIZE, ROUND_BUTTON_SIZE);
    PlayButton.setPos(270, 300);

    HomeButton.setSize(ROUND_BUTTON_SIZE, ROUND_BUTTON_SIZE);
    HomeButton.setPos(470, 300);

    RoundExitButton.setSize(ROUND_BUTTON_SIZE, ROUND_BUTTON_SIZE);
    RoundExitButton.setPos(670, 300);

    //-----GameStateInit-----
    backToMenu = false;
    game_over = false;
    game_paused = false;
    quit = false;
    exit_game = false;

    ScoreBoard_PosY = SCREEN_HEIGHT+10;

    //-----Renderer Init-----
    SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );
}

void HandleMenu(){
    SDL_Event e_mouse;
    while (SDL_PollEvent(&e_mouse) != 0)
    {
        if (e_mouse.type == SDL_QUIT) {
                ExitSound();
                menu = false;
        }

        quit_game = false;

        StartButton.handleEvent(&e_mouse, menu, play);
        ExitButton.handleEvent(&e_mouse, menu, quit_game);
        RoundExitButton.handleEvent(&e_mouse, menu, quit_game);

        if (quit_game == true){
            ExitSound();
            close();
        }
    }
    SDL_RenderClear(gRenderer);

    RenderScrollingBackground();
    RenderScrollingGround();
    StartBackground_Texture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    gMonkeyRenderRunning();

    StartButton.render();
    ExitButton.render();

    SDL_RenderPresent(gRenderer);
}

void gMonkeyHandleHigherPath(){

    for(int ID = 0; ID < HIGHER_PATH_COUNT; ++ID){

        double PathPosX = PathPosX_Carry[ID];
        double PathPosX_End = PathPosX + PATH_WIDTH[ID];

        int gMonkey_HigherPath_PosY;
        if(ID <= UP_PATH2_ID) gMonkey_HigherPath_PosY = MONKEY_POSY_LEVEL[POSY_UP_ID];
        else gMonkey_HigherPath_PosY = MONKEY_POSY_LEVEL[POSY_AIR_ID];

        if ((gMonkeyPos.first + MONKEY_WIDTH - 10) >= PathPosX && gMonkeyPos.first + 40 <= PathPosX_End){
            if (gMonkeyState == STATE_FALLNPR || gMonkeyState == STATE_FALLPARA){

                if (gMonkeyPos.second >= gMonkey_HigherPath_PosY && gMonkeyPos.second <= gMonkey_HigherPath_PosY + MONKEY_JUMPING_SPEED){
                    JumpBreak = 0;
                    gMonkeyPos.second = gMonkey_HigherPath_PosY;
                    gMonkeyState = STATE_RUN;
                }
            }
        }
        else if(gMonkeyState == STATE_RUN && gMonkeyPos.second == gMonkey_HigherPath_PosY){
                if (gMonkeyPos.first + 40 > PathPosX_End && gMonkeyPos.first <= PathPosX_End){
                    gMonkeyPos.second += MONKEY_JUMPING_SPEED;
                    gMonkeyState = STATE_FALLNPR;
                    //cout << ID << " ";     //debug only
                }
        }

    }

}


void gMonkeyHandleChangeSpeed(){
    MONKEY_ANIMATION_SPEED = BASE_MONKEY_SPEED*0.75;
    MONKEY_JUMPING_SPEED = MONKEY_RUNNING_SPEED*2.5;
}

void gMonkeyHandleMoving(){

    if(gMonkeyState == STATE_RUN) gMonkeyHandleRunning();

    if(gMonkeyState == STATE_JUMP) gMonkeyHandleJumping();

    if(gMonkeyState == STATE_FALLNPR) gMonkeyHandleFallNPR();

    if(gMonkeyState == STATE_FALLPARA) gMonkeyHandleFallPARA();

    MONKEY_RUNNING_SPEED = BASE_MONKEY_SPEED + (1.0*gTimer.getTicks()/50000);
}


void UpdateHighScore(int &BestDistance, int &BestBanana){

    int oldBestDistance, oldBestBanana;
    fstream HighScoreFile;
    HighScoreFile.open("HighScoreFile", ios::in);
    HighScoreFile >> oldBestDistance >> oldBestBanana;
    if (BestDistance <= oldBestDistance || BestBanana <= oldBestBanana){
        BestDistance = oldBestDistance;
        BestBanana = oldBestBanana;
    }
    else DeathMessage = "NEW BEST!";
    HighScoreFile.close();
    HighScoreFile.open("HighScoreFile", ios::out);
    HighScoreFile << BestDistance << " " << BestBanana;
    HighScoreFile.close();

}

void DeathScreenShot(){
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(gRenderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, "Material/DeathScreen/DeathScreen.bmp");
    if(!DeathScreen.loadFromFile("Material/DeathScreen/DeathScreen.bmp"))
        printf( "Failed to load DeathScreen texture image!\n" );
}

void handleTopLeftScore(){
    gRunDistance += MONKEY_RUNNING_SPEED;
    scoreNow = longLongToString(gRunDistance/80) + " m";
    bananaScoreNow = longLongToString(Banana_Score) + " Banana";
    if (Banana_Score >= 2) bananaScoreNow += 's';

    gTextTexture.loadFromRenderedText( scoreNow, ScoreBorderColor, gBorderFont);
    gTextTexture.render(10, 40);

    gTextTexture.loadFromRenderedText( scoreNow, ScoreColor, gFont);
    gTextTexture.render(12, 39);

    gTextTexture.loadFromRenderedText( bananaScoreNow, ScoreBorderColor, gBorderFont);
    gTextTexture.render(10, 70);

    gTextTexture.loadFromRenderedText( bananaScoreNow, ScoreColor, gFont);
    gTextTexture.render(12, 69);
}

//----------Game Stopped----------

void handleDeathFuncion(SDL_Event e_mouse){
    AgainButton.handleEvent(&e_mouse, game_over, play);
    ExitButton.handleEvent(&e_mouse, game_over, exit_game);
}

void HandlePauseFunction(SDL_Event e_mouse){
    PlayButton.handleEvent(&e_mouse, game_paused, play);
    HomeButton.handleEvent(&e_mouse, game_paused, backToMenu);
    RoundExitButton.handleEvent(&e_mouse, game_paused, exit_game);

    if (!game_paused) {
        if(Mix_PausedMusic()) Mix_ResumeMusic();
        gTimer.unpause();
    }

    if(backToMenu){
        Mix_HaltChannel(-1);
        quit = true;
        play = false;
    }
}

void HandleStopFunction(){

    if (game_over){
        play = false;
        quit = true;
        gTimer.stop();
    }
    else gTimer.pause();

    exit_game = false;
    SDL_Event e_mouse;

    while (SDL_PollEvent(&e_mouse) != 0)
    {
        if (e_mouse.type == SDL_QUIT){
            ExitSound();
            close();
        }

        if (game_over) handleDeathFuncion(e_mouse);

        else if (game_paused) HandlePauseFunction(e_mouse);

        if (exit_game){
            ExitSound();
            close();
        }
    }
}

//----------Stop Screen----------
void getDeathScore(){
    int BestDistance = gRunDistance/80, BestBanana = Banana_Score;
    UpdateHighScore(BestDistance, BestBanana);

    bananaScoreNow = "Banana:  ";
    if (Banana_Score >= 2) bananaScoreNow = "Bananas:  ";

    scoreNow = "Distance:  " + longLongToString(gRunDistance/80) + " (Best " + longLongToString(BestDistance) + ")";
    bananaScoreNow += longLongToString(Banana_Score) + " (Best " + longLongToString(BestBanana) + ")";
}

void handleDeathFloatingObject(){

    if (ScoreBoard_PosY > 30) ScoreBoard_PosY -= 15;
    ExitButton.setPos(570, ScoreBoard_PosY + 380);
    AgainButton.setPos(200, ScoreBoard_PosY + 380);

    ScoreBoard.render(SCORE_BOARD_POSX, ScoreBoard_PosY, SCORE_BOARD_WIDTH, SCORE_BOARD_HEIGHT);

    RenderScoreWithPosY(DeathMessage, ScoreBoard_PosY + 115);
    RenderScoreWithPosY(scoreNow, ScoreBoard_PosY + 169);
    RenderScoreWithPosY(bananaScoreNow, ScoreBoard_PosY + 229);

    AgainButton.render();
    ExitButton.render();
}

void HandlePauseFloatingObject(){
    Paused_Text.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    PlayButton.render();
    HomeButton.render();
    RoundExitButton.render();
}

void HandleStopScreen(){

    getDeathScore();

    SDL_RenderClear(gRenderer);

    DeathScreen.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (game_over) handleDeathFloatingObject();

    else if (game_paused) HandlePauseFloatingObject();

    SDL_RenderPresent(gRenderer);
}
