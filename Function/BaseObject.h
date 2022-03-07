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
    bool loadFromFile(std::string path);
    void free();
    void render(int x, int y);
    int getWidth();
    int getHeight();

};


#endif BASE_OBJECT_H_
