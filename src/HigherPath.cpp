#include "HigherPath.h"

HigherPath::HigherPath(){
}

HigherPath::HigherPath(int ID){
    this->ID = ID;
    HigherPath_Texture = NULL;

    if (ID == UP_PATH1_ID){
        pathWidth = UP_PATH1_WIDTH;
        posY = HIGH_PATH_X1_POSY;
    }

    if (ID == UP_PATH2_ID){
        pathWidth = UP_PATH2_WIDTH;
        posY = HIGH_PATH_X1_POSY;
    }

    if (ID == AIR_PATH1_ID){
        pathWidth = AIR_PATH1_WIDTH;
        posY = HIGH_PATH_X2_POSY;
    }

    if (ID == AIR_PATH2_ID){
        pathWidth = AIR_PATH2_WIDTH;
        posY = HIGH_PATH_X2_POSY;
    }
    updateX(posX);
}

HigherPath::~HigherPath(){
    free();
}

void HigherPath::free(){
    if (HigherPath_Texture != NULL){
        SDL_DestroyTexture(HigherPath_Texture);
        HigherPath_Texture = NULL;
    }
}

void HigherPath::updateX(int &posX){

    posX = rand() % (PATH_SCREEN_SPACING) + SCREEN_WIDTH;
    int posX_End = posX + pathWidth;

    int ID_Col = (ID % 2) ? (ID + 1) : (ID - 1);

    if ((posX >= PathPosX_Carry[ID_Col].first && posX <= PathPosX_Carry[ID_Col].second)
        || (posX <= PathPosX_Carry[ID_Col].first && posX_End >= PathPosX_Carry[ID_Col].first)){
         posX = (rand() % PATH_SCREEN_SPACING) + PathPosX_Carry[ID_Col].second;
         posX_End = posX + pathWidth;
    }

    PathPosX_Carry[ID] = make_pair(posX, posX_End);
}

bool HigherPath::loadFromFile(string path, SDL_Renderer *gRenderer){

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
        SDL_FreeSurface(loadedSurface);

    }

    HigherPath_Texture = newTexture;
    return HigherPath_Texture != NULL;
}

void HigherPath::render(SDL_Renderer* gRenderer, int wSize, int hSize){

    SDL_Rect renderQuad = {posX, posY, wSize, hSize};

    SDL_RenderCopy(gRenderer, HigherPath_Texture, NULL, &renderQuad);
}

void HigherPath::Move(int speed){

    posX -= speed;
    PathPosX_Carry[ID].first -= speed;
    PathPosX_Carry[ID].second -= speed;
    if(posX < -pathWidth) updateX(posX);
}
