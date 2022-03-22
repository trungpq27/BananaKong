#include "gMonkey.h"

//<----------Object Class----------
gMonkey::gMonkey() : BaseObject(){
    state = GROUNDED;
}

gMonkey::~gMonkey(){
    BaseObject::free();
    state = 0;
}

bool gMonkey::getState(int status){
    return state == status;
}

void gMonkey::SetState(int setTo){

    if (setTo != NULL) {
        state = setTo;
        return;
    }

    if (state == GROUNDED && currentKeyStates[SDL_SCANCODE_UP]) state = JUMP;


    if (gMonkey_Pos.second > JumpTo && gMonkey_Pos.second != Ground.second) return;

}


//<----------Function---------
void MonkeyFrameControl(int &frame, double speed){
    ++frame;
    if (frame / speed >= MONKEY_RUNNING_FRAME_COUNT) frame = 0;
}
