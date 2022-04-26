#include "Button.h"

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

void Button::render(SDL_Renderer *gRenderer){
    BaseObject::render(gRenderer, mPosition.x, mPosition.y, wSize, hSize);
}
