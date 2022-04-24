#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "BaseFunc.h"

const int SCORE_BOARD_HEIGHT = 400;
const int SCORE_BOARD_WIDTH = SCORE_BOARD_HEIGHT*1.8;


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

    bool loadFromFile(std::string path, SDL_Renderer *gRenderer);

    void free();

    void render(SDL_Renderer* gRenderer, double x, double y, int wSize, int hSize, SDL_Rect* clip = NULL);

    int getWidth();

    int getHeight();

};

//----------End of Object Class--------->

#endif //BASE_OBJECT_H_
