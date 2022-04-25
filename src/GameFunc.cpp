#include "GameFunc.h"

void Exit_Sound(Mix_Chunk *SeeYa){
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

void gMonkeyHandleHigherPath(int &gMonkeyState, pair<int, int> &gMonkey_Pos, pair<double, double> *PathPosX_Carry, int &FallTo_Pos, int MONKEY_JUMPING_SPEED, int &JumpBreak){

    for(int ID = 1; ID <= HIGHER_PATH_COUNT; ++ID){

        if ((gMonkey_Pos.first + MONKEY_WIDTH - 20) >= PathPosX_Carry[ID].first && gMonkey_Pos.first + 50 <= PathPosX_Carry[ID].second){

            int gMonkey_HigherPath_PosY;
            if(ID <= UP_PATH2_ID) gMonkey_HigherPath_PosY = gMonkey_X1_PosY;
            else gMonkey_HigherPath_PosY = gMonkey_X2_PosY;

            if (gMonkeyState == STATE_FALLNPR || gMonkeyState == STATE_FALLPARA){

                if (gMonkey_Pos.second >= gMonkey_HigherPath_PosY && gMonkey_Pos.second <= gMonkey_HigherPath_PosY + MONKEY_JUMPING_SPEED){
                    JumpBreak = 0;
                    gMonkey_Pos.second = gMonkey_HigherPath_PosY;
                    gMonkeyState = STATE_RUN;
                }
            }

        }
        else if(gMonkeyState == STATE_RUN && gMonkey_Pos.first + 50 > PathPosX_Carry[ID].second && gMonkey_Pos.first <= PathPosX_Carry[ID].second){
                if ((ID <= UP_PATH2_ID && gMonkey_Pos.second == gMonkey_X1_PosY) || (ID >= AIR_PATH1_ID && gMonkey_Pos.second == gMonkey_X2_PosY)){
                    gMonkey_Pos.second += MONKEY_JUMPING_SPEED;
                    gMonkeyState = STATE_FALLNPR;
                    //cout << ID << " ";     //debug only
                }
        }

    }

}


void gMonkeyHandleMoving(SDL_Renderer* gRenderer, int &JumpBreak, int &gMonkeyState, pair <int, int> &gMonkey_Pos, int &JumpTo_Pos, int &FallTo_Pos,
                         gMonkey &gMonkeyRunning_Texture, SDL_Rect *gMonkeyRunning_Clips, gMonkey &gMonkeyJumping_Texture, gMonkey &gMonkeyFallNPR_Texture,
                         gMonkey &gMonkeyFallPARA_Texture, double &MONKEY_RUNNING_SPEED, int &MONKEY_RUNNING_FRAME, int &MONKEY_ANIMATION_SPEED,
                         int &MONKEY_JUMPING_SPEED, Timer &gTimer, Mix_Chunk *gMonkeyJump_Sound){

    //cout << gMonkeyState << " " << gMonkey_Pos.second << " " << gMonkey_X1_PosY << " " << FallTo_Pos << "\n";  //debug only
    //cout << JumpBreak << "\n";  //debug only
    SDL_Rect* currentClip = NULL;

    if(gMonkeyState == STATE_RUN){
        JumpBreak += MONKEY_RUNNING_SPEED;
        setMonkeyPos(gMonkeyRunning_Texture, gMonkey_Pos);
        if(currentKeyStates[ SDL_SCANCODE_DOWN ]){
                Mix_PlayChannel(-1, gMonkeyJump_Sound, 0);
                gMonkey_Pos.second += MONKEY_JUMPING_SPEED;
                gMonkeyState = STATE_FALLNPR;
        }
        if((currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_SPACE ]) && JumpBreak >= BreakDistance){
            JumpTo_Pos = gMonkey_JumpTo_Y1;
            if (gMonkey_Pos.second == gMonkey_X1_PosY) JumpTo_Pos = gMonkey_JumpTo_Y2;
            if (gMonkey_Pos.second == gMonkey_X2_PosY) JumpTo_Pos = 0;
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
        setMonkeyPos(gMonkeyJumping_Texture, gMonkey_Pos);
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
        setMonkeyPos(gMonkeyFallNPR_Texture, gMonkey_Pos);
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
        setMonkeyPos(gMonkeyFallPARA_Texture, gMonkey_Pos);

        if(gMonkey_Pos.second < FallTo_Pos && !(currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_SPACE ])){
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


void UpdateHighScore(int &BestDistance, int &BestBanana, string &DeathMessage){

    int oldBestDistance, oldBestBanana;
    fstream HighScoreFile;
    HighScoreFile.open("HighScoreFile", ios::in);
    HighScoreFile >> oldBestDistance >> oldBestBanana;
    if (BestDistance <= oldBestDistance || BestBanana <+ oldBestBanana){
        BestDistance = oldBestDistance;
        BestBanana = oldBestBanana;
    }
    else DeathMessage = "NEW BEST!";
    HighScoreFile.close();
    HighScoreFile.open("HighScoreFile", ios::out);
    HighScoreFile << BestDistance << " " << BestBanana;
    HighScoreFile.close();

}

void DeathScreenShot(BaseObject &DeathScreen, SDL_Renderer* gRenderer){
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(gRenderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, "Material/DeathScreen/DeathScreen.bmp");
    if(!DeathScreen.loadFromFile("Material/DeathScreen/DeathScreen.bmp", gRenderer))
        printf( "Failed to load DeathScreen texture image!\n" );
}

void HandleGameOver(bool &game_over, bool &game_paused, bool &play, bool &quit, Timer &gTimer, Button &AgainButton, Button &ExitButton, Button &PauseButton,
                    Mix_Chunk *Hover_Sound, Mix_Chunk *gClick_Sound, Mix_Chunk *SeeYa){

    if (game_over) play = false, quit = true, gTimer.stop();
    else gTimer.pause();
    bool exit = false;
    SDL_Event e_mouse;
    while (SDL_PollEvent(&e_mouse) != 0)
    {
        if (e_mouse.type == SDL_QUIT){
            Exit_Sound(SeeYa);
            game_over = false;
        }

        if (game_over){
            AgainButton.handleEvent(&e_mouse, game_over, play, Hover_Sound, gClick_Sound);
            ExitButton.handleEvent(&e_mouse, game_over, exit, Hover_Sound, gClick_Sound);
        }

        else if (game_paused){
            PauseButton.handleEvent(&e_mouse, game_paused, play, Hover_Sound, gClick_Sound);
            if (!game_paused) {
                if(Mix_PausedMusic()) Mix_ResumeMusic();
                gTimer.unpause();
            }
        }

        if (exit){
            Exit_Sound(SeeYa);
            game_over = false;
            game_paused = false;
        }
    }
}

void HandleDeathScreen (SDL_Renderer* gRenderer, BaseObject &DeathScreen, bool &game_over, BaseObject &ScoreBoard, BaseObject &Paused_Text, gText &gTextTexture,
                        TTF_Font *gDeathFont, TTF_Font *gDeathBorderFont, Button &AgainButton, Button &ExitButton, Button &PauseButton, string scoreNow,
                        string bananaScoreNow, string DeathMessage){
    DeathScreen.render(gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (game_over){
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
    else {
        Paused_Text.render(gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        PauseButton.render(gRenderer);
    }

}
