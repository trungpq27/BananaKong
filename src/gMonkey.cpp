#include "gMonkey.h"

//<----------Object Class----------
gMonkey::gMonkey() : BaseObject(){
    posX = MONKEY_STABLE_POSX;
    posY = MONKEY_STABLE_POSY;
}

gMonkey::~gMonkey(){
    BaseObject::free();
    posX = 0;
    posY = 0;
}

void gMonkey::render(SDL_Rect* clip){
    BaseObject::render(posX, posY, MONKEY_WIDTH, MONKEY_HEIGHT, clip);
}

int gMonkey::getPosX(){
    return posX;
}

int gMonkey::getPosY(){
    return posY;
}

void gMonkey::setPosX(int posX){
    this->posX = posX;
}

void gMonkey::setPosY(int posY){
    this->posY = posY;
}

//<----------Declare----------
int gRunDistance = 0;
int gMonkeyState = STATE_RUN;
int JumpBreak = 0;
int jumpToPos = 0;
bool gMonkeyOnObstacle = false;
pair <int, int> gMonkeyPos = {MONKEY_STABLE_POSX, MONKEY_STABLE_POSY};

int MONKEY_RUNNING_FRAME = 0;
int MONKEY_JUMPING_SPEED;
double MONKEY_RUNNING_SPEED = BASE_MONKEY_SPEED;
int MONKEY_ANIMATION_SPEED = BASE_MONKEY_SPEED*0.75;

gMonkey gMonkeyRunning_Texture;
gMonkey gMonkeyJumping_Texture;
gMonkey gMonkeyFallNPR_Texture;
gMonkey gMonkeyFallPARA_Texture;

SDL_Rect gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME_COUNT];


//<----------Object Function----------

bool ScanCodeUpCheck(){
    return currentKeyStates[ SDL_SCANCODE_UP ] || currentKeyStates[ SDL_SCANCODE_SPACE ];
}

void gMonkeyRenderRunning(){

    SDL_Rect* currentClip = &gMonkeyRunning_Clips[MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED];
    ++MONKEY_RUNNING_FRAME;

    if (MONKEY_RUNNING_FRAME / MONKEY_ANIMATION_SPEED >= MONKEY_RUNNING_FRAME_COUNT){
        MONKEY_RUNNING_FRAME = 0;
    }

    gMonkeyRunning_Texture.setPosY(gMonkeyPos.second);
    gMonkeyRunning_Texture.render(currentClip);
    return;
}

void gMonkeyHandleInstantDown(){
    Mix_PlayChannel(-1, gMonkeyJump_Sound, 0);
    gMonkeyPos.second = min(gMonkeyPos.second + MONKEY_JUMPING_SPEED, MONKEY_STABLE_POSY);
    gMonkeyState = STATE_FALLNPR;
    return;
}

void gMonkeyHandleFallWithSpeed(gMonkey &gMonkeyTexture, double speed){
    gMonkeyPos.second = min(gMonkeyPos.second + speed, (double) MONKEY_STABLE_POSY);
    gMonkeyTexture.setPosY(gMonkeyPos.second);
    gMonkeyTexture.render();
}

void gMonkeyRenderJumping(){
    gMonkeyPos.second = max(0, gMonkeyPos.second - MONKEY_JUMPING_SPEED);
    gMonkeyJumping_Texture.setPosY(gMonkeyPos.second);
    gMonkeyJumping_Texture.render();
}



void gMonkeyHandleRunning(){

    JumpBreak += MONKEY_RUNNING_SPEED;
    if(currentKeyStates[ SDL_SCANCODE_DOWN ]){
        if(!gMonkeyOnObstacle && gMonkeyPos.second < MONKEY_STABLE_POSY){
            gMonkeyHandleInstantDown();
        }
    }

    if(ScanCodeUpCheck() && JumpBreak >= JUMP_BREAK_DISTANCE){
        Mix_PlayChannel(-1, gMonkeyJump_Sound, 0);
        jumpToPos = max(0, gMonkeyPos.second - MONKEY_JUMP_DISTANCE);
        gMonkeyState = STATE_JUMP;
    }

    else gMonkeyRenderRunning();

}

void gMonkeyHandleJumping(){

    if(currentKeyStates[ SDL_SCANCODE_DOWN ]){
        gMonkeyHandleInstantDown();
        return;
    }

    switch (gMonkeyPos.second > jumpToPos){

        case 1:
            gMonkeyRenderJumping();
            break;

        case 0:
            if (ScanCodeUpCheck()) gMonkeyState = STATE_FALLPARA;
            else gMonkeyState = STATE_FALLNPR;
    }

}


void gMonkeyHandleFallNPR(){

    switch(gMonkeyPos.second < MONKEY_STABLE_POSY){

        case 1:
            if (ScanCodeUpCheck()) gMonkeyState = STATE_FALLPARA;

            else gMonkeyHandleFallWithSpeed(gMonkeyFallNPR_Texture, MONKEY_JUMPING_SPEED);
            break;

        case 0:
            gMonkeyState = STATE_RUN;
            JumpBreak = JUMP_BREAK_DISTANCE;
    }
}

void gMonkeyHandleFallPARA(){

    switch(gMonkeyPos.second < MONKEY_STABLE_POSY){

        case 1:
            if (!ScanCodeUpCheck()) gMonkeyState = STATE_FALLNPR;

            else gMonkeyHandleFallWithSpeed(gMonkeyFallPARA_Texture, MONKEY_RUNNING_SPEED/3);
            break;

        case 0:
            gMonkeyState = STATE_RUN;
            JumpBreak = 0;
    }

}

//----------Load Media----------
bool isLoadMonkeyOK(){
    bool success = true;
    if(!gMonkeyJumping_Texture.loadFromFile("Material/Characters/Monkey/MonkeyJump.png")){
        printf( "Failed to load monkeyJump texture image!\n" );
        success = false;
    }

    if(!gMonkeyFallNPR_Texture.loadFromFile("Material/Characters/Monkey/MonkeyFall_NoPara.png")){
        printf( "Failed to load monkeyFallNoPara texture image!\n" );
        success = false;
    }

    if(!gMonkeyFallPARA_Texture.loadFromFile("Material/Characters/Monkey/MonkeyFall_Para.png")){
        printf( "Failed to load monkeyFallPara texture image!\n" );
        success = false;
    }

    if(!gMonkeyRunning_Texture.loadFromFile("Material/Characters/Monkey/MonkeyRun.png")){
        printf( "Failed to load monkeyRun texture image!\n" );
        success = false;
    }
    else {
            gMonkeyRunning_Clips[0].x = 115 * 0;
            gMonkeyRunning_Clips[0].y = 0;
            gMonkeyRunning_Clips[0].h = 151;
            gMonkeyRunning_Clips[0].w = 115;

            gMonkeyRunning_Clips[1].x = 115 * 1;
            gMonkeyRunning_Clips[1].y = 0;
            gMonkeyRunning_Clips[1].h = 151;
            gMonkeyRunning_Clips[1].w = 115;

            gMonkeyRunning_Clips[2].x = 115 * 2;
            gMonkeyRunning_Clips[2].y = 0;
            gMonkeyRunning_Clips[2].h = 151;
            gMonkeyRunning_Clips[2].w = 115;

            gMonkeyRunning_Clips[3].x = 115 * 3;
            gMonkeyRunning_Clips[3].y = 0;
            gMonkeyRunning_Clips[3].h = 151;
            gMonkeyRunning_Clips[3].w = 115;

            gMonkeyRunning_Clips[4].x = 115 * 4;
            gMonkeyRunning_Clips[4].y = 0;
            gMonkeyRunning_Clips[4].h = 151;
            gMonkeyRunning_Clips[4].w = 115;

            gMonkeyRunning_Clips[5].x = 115 * 5;
            gMonkeyRunning_Clips[5].y = 0;
            gMonkeyRunning_Clips[5].h = 151;
            gMonkeyRunning_Clips[5].w = 115;

            gMonkeyRunning_Clips[6].x = 115 * 6;
            gMonkeyRunning_Clips[6].y = 0;
            gMonkeyRunning_Clips[6].h = 151;
            gMonkeyRunning_Clips[6].w = 115;

            gMonkeyRunning_Clips[7].x = 115 * 7;
            gMonkeyRunning_Clips[7].y = 0;
            gMonkeyRunning_Clips[7].h = 151;
            gMonkeyRunning_Clips[7].w = 115;
    }

    return success;
}

void closeMonkey(){
    gMonkeyRunning_Texture.free();
    gMonkeyJumping_Texture.free();
    gMonkeyFallNPR_Texture.free();
    gMonkeyFallPARA_Texture.free();
    StartBackground_Texture.free();
    DeathScreen.free();
    Paused_Text.free();
}
