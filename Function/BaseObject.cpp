#include "BaseObject.h"

BaseObject::BaseObject(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

BaseObject::~BaseObject(){
    free();
}

bool BaseObject::loadFromFile(std::string path){

    free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL){
        printf ("%s IMG Load failed: %s" , path.c_str(), IMG_GetError() );
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if(newTexture == NULL){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

void BaseObject::free(){

    if (mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void BaseObject::render(int x, int y){

    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);

}

int BaseObject::getWidth(){
    return mWidth;
}

int BaseObject::getHeight(){
    return mHeight;
}

