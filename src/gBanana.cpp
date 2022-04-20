#include "gBanana.h"

gBanana::gBanana(list<pair<double, int>> &BananaPos) : BaseObject(){
    Banana_Sum = 0;
    updateY();
    updateX(posX, BananaPos);
}

gBanana::~gBanana()
{

}

void gBanana::updateY(){
    Y_ID = rand()%4;
    if (Y_ID == 1) posY = 500;
    else if (Y_ID == 2) posY = 360;
    else if (Y_ID == 3) posY = 210;
}

void gBanana::updateX(double &PosX, list<pair<double, int>> &BananaPos){

    Amount = 3 + (rand() % 4);
    Banana_Sum += Amount;

    bool rand_ok = 0;
    while (!rand_ok){
        rand_ok = 1;
        posX = SCREEN_WIDTH + BANANA_SPACING + (rand() % BANANA_SPACING);
        if (posX <= BananaPos.back().first + BANANA_WIDTH) posX = BananaPos.back().first + BANANA_SPACING + (rand() % BANANA_SPACING);
        if (posX <= ObstaclePosX_Carry[Y_ID][1].second || posX + BANANA_WIDTH*Amount <= ObstaclePosX_Carry[Y_ID][1].first) rand_ok = 0;
        if (posX <= ObstaclePosX_Carry[Y_ID][2].second || posX + BANANA_WIDTH*Amount <= ObstaclePosX_Carry[Y_ID][2].first) rand_ok = 0;
    }

    for(int i = 1; i <= Amount; ++i){
        BananaPos.push_back({posX, posY});
        posX = posX + BANANA_WIDTH;
    }
}

void gBanana::render(SDL_Renderer* gRenderer, int wSize, int hSize, double speed, list<pair<double, int>> &BananaPos){

    if (BananaPos.front().first <= SCREEN_WIDTH/2 && BananaPos.front().first + BANANA_WIDTH + 1 > SCREEN_WIDTH/2){
        updateY();
        updateX(posX, BananaPos);
    }
    int Carry = Banana_Sum;
    while(Carry--){

        pair <double, int> posNow = BananaPos.front();
        BananaPos.pop_front();

        posNow.first -= speed;
        BaseObject::render(gRenderer, posNow.first, posNow.second, wSize, hSize);

        if(posNow.first + BANANA_WIDTH >= 0) BananaPos.push_back(posNow);
        else Banana_Sum--;

    }
}

void gBanana::Handle_Monkey(pair <int, int> gMonkey_Pos, list<pair<double, int>> &BananaPos, int &Banana_Score){

    int Carry = BananaPos.size();
    while(Carry--){
        pair <double, int> Banana_posNow = BananaPos.front();
        BananaPos.pop_front();

        if ((Banana_posNow.second + BANANA_HEIGHT >= gMonkey_Pos.second && Banana_posNow.second <= gMonkey_Pos.second + MONKEY_HEIGHT) &&
            (Banana_posNow.first + BANANA_WIDTH >= gMonkey_Pos.first && Banana_posNow.first <= gMonkey_Pos.first + MONKEY_WIDTH - 30)){
                Banana_Score++;
                Banana_Sum--;
            }
        else BananaPos.push_back(Banana_posNow);

    }
}
