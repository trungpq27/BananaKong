#include "BaseObj.h"


//<----------Object Class---------

BaseObject::BaseObject(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

BaseObject::~BaseObject(){
    free();
}

bool BaseObject::loadFromFile(string path){

    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == NULL) {
        printf ("%s IMG Load failed: %s" , path.c_str(), IMG_GetError() );
    }
    else {

        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if (newTexture == NULL){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        else{
            //get image dimension
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

void BaseObject::render(double x, double y, int wSize, int hSize, SDL_Rect* clip){

    SDL_Rect renderQuad = {x, y, wSize, hSize};

    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int BaseObject::getWidth(){
    return mWidth;
}

int BaseObject::getHeight(){
    return mHeight;
}

//----------End of Object Class--------->

//---------Declare----------
BaseObject ScoreBoard;
string DeathMessage;
string scoreNow;
string bananaScoreNow;
int ScoreBoard_PosY = SCREEN_HEIGHT+10;

BaseObject Paused_Text;
BaseObject DeathScreen;
BaseObject StartBackground_Texture;

//----------Load Media---------->
bool isLoadBaseObjectOK(){

    bool success = true;

    //-----ScoreBoard-----
	if(!ScoreBoard.loadFromFile("Material/Others/ScoreBoard.png")){
        printf( "Failed to load ScoreBoard texture image!\n" );
        success = false;
    }

    //-----PlayPauseText-----
    if( !StartBackground_Texture.loadFromFile( "Material/Background/Title.png" ) ){
        printf( "Failed to load StartBackground layer %d texture image!\n");
        success = false;
    }
    if( !Paused_Text.loadFromFile( "Material/Menu/PlayPause/Paused.png" ) ){
        printf( "Failed to load Paused_Text layer %d texture image!\n");
        success = false;
    }
    return success;
}

void closeBaseObject(){
    Paused_Text.free();
    DeathScreen.free();
    ScoreBoard.free();
}
