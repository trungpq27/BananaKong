#include "Button.h"

//<----------Object Class----------

Button::Button()
{
    hover = false;
    mPosition.x = 0;
    mPosition.y = 0;
    posX = 0;
    posY = 0;
}

Button::~Button()
{
    //dtor
}

void Button::setSize(int wSize, int hSize){
    this->wSize = wSize;
    this->hSize = hSize;
    oldW = wSize, oldH = hSize;
}

void Button::setPos( int x, int y )
{
    posX = x;
    posY = y;
    mPosition.x = x;
    mPosition.y = y;
}

void Button::handleEvent( SDL_Event* e_mouse, bool &menu, bool &state)
{
    if( e_mouse->type == SDL_MOUSEMOTION || e_mouse->type == SDL_MOUSEBUTTONDOWN || e_mouse->type == SDL_MOUSEBUTTONUP )
    {
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;

        if((x < mPosition.x) || (x > mPosition.x + wSize) || (y < mPosition.y) || (y > mPosition.y + hSize)){
            hover = false;
            inside = false;

            wSize = oldW;
            hSize = oldH;
            mPosition.x = posX;
            mPosition.y = posY;
        }

        if(inside) {

            if (hover == false){
                Mix_PlayChannel(-1, Hover_Sound, 0);
                hover = true;
            }

            wSize = oldW + 10;
            hSize = oldH + 10;
            mPosition.x = posX - 5;
            mPosition.y = posY - 5;

            if (e_mouse->type == SDL_MOUSEBUTTONDOWN){
                menu = false;
                state = true;
                Mix_PlayChannel(-1, gClick_Sound, 0);
            }
        }
    }
}

void Button::render(){
    BaseObject::render(mPosition.x, mPosition.y, wSize, hSize);
}

//----------End of Object Class---------->

//----------Declare----------
Button StartButton;
Button ExitButton;
Button AgainButton;

Button PlayButton;
Button PauseButton;
Button RoundExitButton;
Button HomeButton;

//----------Load Media----------
bool isLoadButtonOK(){
    bool success = true;
    if( !StartButton.loadFromFile( "Material/Menu/Button/Start.png" ) ){
        printf( "Failed to load StartButton layer %d texture image!\n");
        success = false;
    }

    if( !ExitButton.loadFromFile( "Material/Menu/Button/Exit.png" ) ){
        printf( "Failed to load ExitButton layer %d texture image!\n");
        success = false;
    }

    if( !AgainButton.loadFromFile( "Material/Menu/Button/Again.png" ) ){
        printf( "Failed to load AgainButton layer %d texture image!\n");
        success = false;
    }


    if( !PlayButton.loadFromFile( "Material/Menu/PlayPause/Play.png" ) ){
        printf( "Failed to load PlayButton layer %d texture image!\n");
        success = false;
    }

    if( !PauseButton.loadFromFile( "Material/Menu/PlayPause/Pause.png" ) ){
        printf( "Failed to load PauseButton layer %d texture image!\n");
        success = false;
    }

    if( !RoundExitButton.loadFromFile( "Material/Menu/PlayPause/Exit.png" ) ){
        printf( "Failed to load RoundExitButton layer %d texture image!\n");
        success = false;
    }

    if( !HomeButton.loadFromFile( "Material/Menu/PlayPause/Home.png" ) ){
        printf( "Failed to load HomeButton layer %d texture image!\n");
        success = false;
    }

    return success;
}

void closeButton(){

    StartButton.free();
    ExitButton.free();
    AgainButton.free();

    PlayButton.free();
    PauseButton.free();
    RoundExitButton.free();
    HomeButton.free();
}
