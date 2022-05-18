#include "gBanana.h"

gBanana::gBanana() : BaseObject::BaseObject(){
}

gBanana::~gBanana()
{
}

void gBanana::init(){
    Banana_Sum = 0;
    updateY();
    updateX();
}

void gBanana::updateY(){
    Y_ID = rand()%3;
    if (Y_ID == 0) posY = 500;
    else if (Y_ID == 1) posY = 360;
    else if (Y_ID == 2) posY = 210;
}

void gBanana::updateX(){

    Amount = 3 + (rand() % 4);
    Banana_Sum += Amount;

    int endMark = -1;
    for(int j = 0; j < OBSTACLE_COUNT; ++j)
        if (endMark < ObstaclePosX_Carry[Y_ID][j] + MAX_OBSTACLE_WIDTH)
            endMark = ObstaclePosX_Carry[Y_ID][j] + MAX_OBSTACLE_WIDTH;

    if (endMark < BananaPos.back().first) endMark = BananaPos.back().first;

    posX = max(endMark, SCREEN_WIDTH) + BANANA_SPACING + (rand() % BANANA_SPACING);

    for(int i = 1; i <= Amount; ++i){
        BananaPos.push_back({posX, posY});
        posX = posX + BANANA_WIDTH;
    }
}

void gBanana::render(){

    if (BananaPos.front().first <= SCREEN_WIDTH/2 && BananaPos.front().first + BANANA_WIDTH + 1 > SCREEN_WIDTH/2){
        updateY();
        updateX();
    }
    int Carry = Banana_Sum;
    while(Carry--){

        pair <double, int> posNow = BananaPos.front();
        if (!BananaPos.empty()) BananaPos.pop_front();

        posNow.first -= MONKEY_RUNNING_SPEED;
        BaseObject::render(posNow.first, posNow.second, BANANA_WIDTH, BANANA_HEIGHT);

        if(posNow.first + BANANA_WIDTH >= 0) BananaPos.push_back(posNow);
        else Banana_Sum--;

    }
}

void gBanana::Handle_Monkey(){

    int Carry = BananaPos.size();
    while(Carry--){
        pair <double, int> Banana_posNow = BananaPos.front();
        if (!BananaPos.empty()) BananaPos.pop_front();

        if ((Banana_posNow.second + BANANA_HEIGHT >= gMonkeyPos.second && Banana_posNow.second <= gMonkeyPos.second + MONKEY_HEIGHT) &&
            (Banana_posNow.first + BANANA_WIDTH >= gMonkeyPos.first && Banana_posNow.first <= gMonkeyPos.first + MONKEY_WIDTH - 30)){
                Banana_Score++;
                Banana_Sum--;
                Mix_PlayChannel( -1, gBananaGet_Sound, 0 );
            }
        else BananaPos.push_back(Banana_posNow);

    }
}

//----------Declare----------
int Banana_Score = 0;
gBanana gBanana_Texture;
list<pair<double, int>> BananaPos;

//----------Function----------
void MoveAndGetBanana(){
    gBanana_Texture.render();
    gBanana_Texture.Handle_Monkey();
}

//----------Load Media----------
bool isLoadBananaOK(){
    bool success = 0;
    if(!gBanana_Texture.loadFromFile("Material/Characters/Banana/Banana.png")){
        printf( "Failed to load Banana texture image!\n" );
        success = false;
    }
    return success;
}

void closeBanana(){
    gBanana_Texture.free();
}
