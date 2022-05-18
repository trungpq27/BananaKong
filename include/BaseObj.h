#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "BaseFunc.h"

const int SCORE_BOARD_HEIGHT = 400;
const int SCORE_BOARD_WIDTH = SCORE_BOARD_HEIGHT*1.8;
const int SCORE_BOARD_POSX = (SCREEN_WIDTH-SCORE_BOARD_WIDTH)/2;


//----------Object Class--------->

class BaseObject
{

private:

    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;

public:
    BaseObject();

    ~BaseObject();

    bool loadFromFile(std::string path);

    void free();

    void render(double x, double y, int wSize, int hSize, SDL_Rect* clip = NULL);

    int getWidth();

    int getHeight();

};

//----------End of Object Class--------->

//-----Declare-----
extern BaseObject ScoreBoard;
extern string DeathMessage;
extern string scoreNow;
extern string bananaScoreNow;

extern BaseObject Paused_Text;
extern BaseObject DeathScreen;
extern BaseObject StartBackground_Texture;

//-----Load Media-----
extern bool isLoadBaseObjectOK();
extern void closeBaseObject();

#endif //BASE_OBJECT_H_
