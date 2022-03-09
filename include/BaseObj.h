#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "BaseFunc.h"

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

    void render(SDL_Renderer* gRenderer, int x, int y, int wSize, int hSize, SDL_Rect* clip = NULL);

    int getWidth();

    int getHeight();

};

#endif //BASE_OBJECT_H_
