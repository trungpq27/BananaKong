#include "Button.h"

Button::Button(int ID)
{
    hover = false;
    this->ID = ID;
    mPosition.x = 0;
    mPosition.y = 0;
    posX = 0;
    posY = 0;
    if (ID == MENU_BUTTON_ID){
        hSize = START_BUTTON_HEIGHT;
        wSize = START_BUTTON_WIDTH;
    }
    else{
        hSize = PLAY_BUTTON_HEIGHT;
        wSize = PLAY_BUTTON_WIDTH;
    }
}

Button::~Button()
{
    //dtor
}

void Button::setPos( int x, int y )
{
    posX = x;
    posY = y;
    mPosition.x = x;
    mPosition.y = y;
}

void Button::handleEvent( SDL_Event* e_mouse, bool &menu, bool &state, Mix_Chunk *Hover_Sound, Mix_Chunk *gClick_Sound)
{
    if( e_mouse->type == SDL_MOUSEMOTION || e_mouse->type == SDL_MOUSEBUTTONDOWN || e_mouse->type == SDL_MOUSEBUTTONUP )
    {
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;

        if((x < mPosition.x) || (x > mPosition.x + wSize) ||
           (y < mPosition.y) || (y > mPosition.y + hSize)){
            hover = false;
            inside = false;
            mPosition.x = posX;
            mPosition.y = posY;
            if (ID == MENU_BUTTON_ID){
                hSize = START_BUTTON_HEIGHT;
                wSize = START_BUTTON_WIDTH;
            }
            else{
                hSize = PLAY_BUTTON_HEIGHT;
                wSize = PLAY_BUTTON_WIDTH;
            }
        }
        if(inside)
        {
            if (hover == false){
                Mix_PlayChannel(-1, Hover_Sound, 0);
                hover = true;
            }

            if (ID == MENU_BUTTON_ID){
                hSize = START_BUTTON_HEIGHT + 10;
                wSize = START_BUTTON_WIDTH + 10;
                mPosition.x = posX - 5;
                mPosition.y = posY - 5;
            }
            else{
                hSize = PLAY_BUTTON_HEIGHT+4;
                wSize = PLAY_BUTTON_WIDTH+4;
                mPosition.x = posX - 2;
                mPosition.y = posY - 2;
            }
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
