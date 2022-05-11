#include "GameFunc.h"

void Exit_Sound(){
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
    Mix_PlayChannel(-1, SeeYa, 0);
    SDL_Delay(1500);
}

string longLongToString(long long x){
    stringstream ss;
    ss << x;
    string str = ss.str();
    return str;
}

void GameInitEverything(SDL_Renderer* gRenderer){

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
    JumpTo_Pos = 310;
    FallTo_Pos = gMonkey_Stable_PosY;
    gMonkey_Pos = {gMonkey_Stable_PosX, gMonkey_Stable_PosY};
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

    //-----Renderer Init-----
    SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );
}

void HandleMenu(SDL_Renderer* gRenderer){
    SDL_Event e_mouse;
    while (SDL_PollEvent(&e_mouse) != 0)
    {
        if (e_mouse.type == SDL_QUIT) {
                Exit_Sound();
                menu = false;
        }

        quit_game = false;

        StartButton.handleEvent(&e_mouse, menu, play);
        ExitButton.handleEvent(&e_mouse, menu, quit_game);
        RoundExitButton.handleEvent(&e_mouse, menu, quit_game);

        if (quit_game == true){
            Exit_Sound();
            close();
        }
    }
    SDL_RenderClear(gRenderer);

    RenderScrollingBackground(gRenderer);
    RenderScrollingGround(gRenderer);
    StartBackground_Texture.render(gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Rect* currentClip = NULL;
    setMonkeyPos(gMonkeyRunning_Texture);
    currentClip = &gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED];
    ++MONKEY_RUNNING_FRAME;
    if (MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED >= MONKEY_RUNNING_FRAME_COUNT) MONKEY_RUNNING_FRAME = 0;
    gMonkeyRunning_Texture.render(gRenderer, currentClip);

    StartButton.render(gRenderer);
    ExitButton.render(gRenderer);

    SDL_RenderPresent(gRenderer);
}

void setMonkeyPos(gMonkey &gMonkey_Texture){
    gMonkey_Texture.setPosX(gMonkey_Pos.first);
    gMonkey_Texture.setPosY(gMonkey_Pos.second);
}


void gMonkeyHandleHigherPath(){

    for(int ID = 0; ID < HIGHER_PATH_COUNT; ++ID){

        double PathPosX = PathPosX_Carry[ID];
        double PathPosX_End = PathPosX + PATH_WIDTH[ID];

        int gMonkey_HigherPath_PosY;
        if(ID <= UP_PATH2_ID) gMonkey_HigherPath_PosY = gMonkey_X1_PosY;
        else gMonkey_HigherPath_PosY = gMonkey_X2_PosY;

        if ((gMonkey_Pos.first + MONKEY_WIDTH - 10) >= PathPosX && gMonkey_Pos.first + 40 <= PathPosX_End){
            if (gMonkeyState == STATE_FALLNPR || gMonkeyState == STATE_FALLPARA){

                if (gMonkey_Pos.second >= gMonkey_HigherPath_PosY && gMonkey_Pos.second <= gMonkey_HigherPath_PosY + MONKEY_JUMPING_SPEED){
                    JumpBreak = 0;
                    gMonkey_Pos.second = gMonkey_HigherPath_PosY;
                    gMonkeyState = STATE_RUN;
                }
            }
        }
        else if(gMonkeyState == STATE_RUN && gMonkey_Pos.second == gMonkey_HigherPath_PosY){
                if (gMonkey_Pos.first + 40 > PathPosX_End && gMonkey_Pos.first <= PathPosX_End){
                    gMonkey_Pos.second += MONKEY_JUMPING_SPEED;
                    gMonkeyState = STATE_FALLNPR;
                    //cout << ID << " ";     //debug only
                }
        }

    }

}

void gMonkeyHandleWalkonObstacle(){

    gMonkey_PosY_ID = POSY_GROUND_ID;
    for (int Level = 0; Level < SCREEN_LEVEL_COUNT; ++Level)
        for (int ID = 0; ID < OBSTACLE_COUNT; ++ID){

        double ObstaclePosX = ObstaclePosX_Carry[Level][ID];
        double ObstaclePosX_End = ObstaclePosX + OBSTACLE_WIDTH[ID];

        int gMonkey_Obstacle_PosY = OBSTACLE_POSY[Level] - MONKEY_HEIGHT + 10;

        if ((gMonkey_Pos.first + MONKEY_WIDTH - 10) >= ObstaclePosX && gMonkey_Pos.first + 50 <= ObstaclePosX_End){
            if (gMonkeyState == STATE_FALLNPR || gMonkeyState == STATE_FALLPARA){

                if (gMonkey_Pos.second >= gMonkey_Obstacle_PosY && gMonkey_Pos.second <= gMonkey_Obstacle_PosY + MONKEY_JUMPING_SPEED){
                    JumpBreak = 0;
                    gMonkey_Pos.second = gMonkey_Obstacle_PosY;
                    gMonkeyState = STATE_RUN;
                    gMonkey_PosY_ID = POSY_ON_OBSTACLE_ID;
                    return;
                    //cout << ObstaclePosX << " " << ObstaclePosX_End << "\n";   //debug only
                }
            }
        }
        else if(gMonkeyState == STATE_RUN && gMonkey_Pos.second == gMonkey_Obstacle_PosY){
                //cout << gMonkey_Pos.first  << " " << ObstaclePosX_End << "\n";
                if ((gMonkey_Pos.first + 50 > ObstaclePosX_End) && (gMonkey_Pos.first <= ObstaclePosX_End)){
                    gMonkey_Pos.second += MONKEY_JUMPING_SPEED;
                    gMonkeyState = STATE_FALLNPR;
                    return;
                }
        }

    }

}


void gMonkeyHandleMoving(SDL_Renderer* gRenderer){
    SDL_Rect* currentClip = NULL;

    if(gMonkeyState == STATE_RUN){
        JumpBreak += MONKEY_RUNNING_SPEED;
        setMonkeyPos(gMonkeyRunning_Texture);
        if(currentKeyStates[ SDL_SCANCODE_DOWN ]){
            if(gMonkey_PosY_ID != POSY_ON_OBSTACLE_ID){
                if (gMonkey_Pos.second < gMonkey_Stable_PosY) Mix_PlayChannel(-1, gMonkeyJump_Sound, 0);
                gMonkey_Pos.second += MONKEY_JUMPING_SPEED;
                gMonkeyState = STATE_FALLNPR;
            }
        }
        if((currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_SPACE ]) && JumpBreak >= BreakDistance){

            JumpTo_Pos = max(0, gMonkey_Pos.second - 190);
            gMonkeyState = STATE_JUMP;
            Mix_PlayChannel(-1, gMonkeyJump_Sound, 0);
        }

        else {
            currentClip = &gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED];
            ++MONKEY_RUNNING_FRAME;
            if (MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED >= MONKEY_RUNNING_FRAME_COUNT) MONKEY_RUNNING_FRAME = 0;
            gMonkeyRunning_Texture.render(gRenderer, currentClip);
        }
    }


    if(gMonkeyState == STATE_JUMP){
        setMonkeyPos(gMonkeyJumping_Texture);
        if(currentKeyStates[ SDL_SCANCODE_DOWN ]){
            Mix_PlayChannel(-1, gMonkeyJump_Sound, 0);
            gMonkeyState = STATE_FALLNPR;
        }
        else{

            if(gMonkey_Pos.second > JumpTo_Pos){
                gMonkeyJumping_Texture.setPosY(gMonkeyJumping_Texture.getPosY()-MONKEY_JUMPING_SPEED);
                gMonkey_Pos.second -= MONKEY_JUMPING_SPEED;
                gMonkeyJumping_Texture.render(gRenderer, currentClip);
            }
            else {
                if (!(currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_SPACE ])) gMonkeyState = STATE_FALLNPR;
                else gMonkeyState = STATE_FALLPARA;
            }
        }
    }


    if(gMonkeyState == STATE_FALLNPR){
        setMonkeyPos(gMonkeyFallNPR_Texture);
        if(gMonkey_Pos.second < FallTo_Pos){

            if ((currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_SPACE ])) gMonkeyState = STATE_FALLPARA;

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
        setMonkeyPos(gMonkeyFallPARA_Texture);

        if(gMonkey_Pos.second < FallTo_Pos && !(currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_SPACE ])){
            gMonkeyState = STATE_FALLNPR;
        }

        if(gMonkey_Pos.second < FallTo_Pos){
            gMonkeyFallPARA_Texture.setPosY(gMonkeyFallPARA_Texture.getPosY()+MONKEY_RUNNING_SPEED);
            gMonkey_Pos.second += MONKEY_RUNNING_SPEED/3;
            gMonkeyFallPARA_Texture.render(gRenderer, currentClip);
        }
        else{
            gMonkeyState = STATE_RUN;
            JumpBreak = 0;
            gMonkey_Pos.second = FallTo_Pos;
        }
    }

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

void DeathScreenShot(SDL_Renderer* gRenderer){
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(gRenderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, "Material/DeathScreen/DeathScreen.bmp");
    if(!DeathScreen.loadFromFile("Material/DeathScreen/DeathScreen.bmp", gRenderer))
        printf( "Failed to load DeathScreen texture image!\n" );
}

void HandleGameOver(){

    if (game_over) play = false, quit = true, gTimer.stop();
    else gTimer.pause();
    bool exit = false;
    SDL_Event e_mouse;
    while (SDL_PollEvent(&e_mouse) != 0)
    {
        if (e_mouse.type == SDL_QUIT){
            Exit_Sound();
            close();
        }

        if (game_over){
            AgainButton.handleEvent(&e_mouse, game_over, play);
            ExitButton.handleEvent(&e_mouse, game_over, exit);
        }

        else if (game_paused){
            PlayButton.handleEvent(&e_mouse, game_paused, play);
            HomeButton.handleEvent(&e_mouse, game_paused, backToMenu);
            RoundExitButton.handleEvent(&e_mouse, game_paused, exit);

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

        if (exit){
            Exit_Sound();
            close();
        }
    }
}

void HandleDeathScreen (SDL_Renderer* gRenderer){

    ExitButton.setPos(570, 400);

    SDL_RenderClear(gRenderer);

    DeathScreen.render(gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (game_over){
        int BestDistance = gRunDistance/80, BestBanana = Banana_Score;
        UpdateHighScore(BestDistance, BestBanana);

        bananaScoreNow = "Banana:  ";
        if (Banana_Score >= 2) bananaScoreNow = "Bananas:  ";

        scoreNow = "Distance:  " + longLongToString(gRunDistance/80) + " (Best " + longLongToString(BestDistance) + ")";
        bananaScoreNow += longLongToString(Banana_Score) + " (Best " + longLongToString(BestBanana) + ")";

        ScoreBoard.render(gRenderer, (SCREEN_WIDTH-SCORE_BOARD_WIDTH)/2, 20, SCORE_BOARD_WIDTH, SCORE_BOARD_HEIGHT);

        gTextTexture.loadFromRenderedText( DeathMessage, DeathScoreBorderColor, gDeathBorderFont, gRenderer);
        gTextTexture.render( gRenderer, gTextTexture.getCenter(), 135);
        gTextTexture.loadFromRenderedText( DeathMessage, DeathScoreColor, gDeathFont, gRenderer);
        gTextTexture.render( gRenderer, gTextTexture.getCenter(), 135);

        gTextTexture.loadFromRenderedText( scoreNow, DeathScoreBorderColor, gDeathBorderFont, gRenderer);
        gTextTexture.render( gRenderer, gTextTexture.getCenter(), 189);
        gTextTexture.loadFromRenderedText( scoreNow, DeathScoreColor, gDeathFont, gRenderer);
        gTextTexture.render( gRenderer, gTextTexture.getCenter(), 189);

        gTextTexture.loadFromRenderedText( bananaScoreNow, DeathScoreBorderColor, gDeathBorderFont, gRenderer);
        gTextTexture.render( gRenderer, gTextTexture.getCenter(), 249);
        gTextTexture.loadFromRenderedText( bananaScoreNow, DeathScoreColor, gDeathFont, gRenderer);
        gTextTexture.render( gRenderer, gTextTexture.getCenter(), 249);

        AgainButton.render(gRenderer);
        ExitButton.render(gRenderer);
    }
    else if (game_paused) {
        Paused_Text.render(gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        PlayButton.render(gRenderer);
        HomeButton.render(gRenderer);
        RoundExitButton.render(gRenderer);
    }
    SDL_RenderPresent(gRenderer);

}
