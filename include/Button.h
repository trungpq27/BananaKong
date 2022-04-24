#ifndef BUTTON_H
#define BUTTON_H

#include "BaseFunc.h"
#include "BaseObj.h"

const int START_BUTTON_HEIGHT = 180;
const int START_BUTTON_WIDTH = START_BUTTON_HEIGHT * 1.936;

const int PLAY_BUTTON_HEIGHT = 40;
const int PLAY_BUTTON_WIDTH = PLAY_BUTTON_HEIGHT;

const int MENU_BUTTON_ID = 1;
const int PAUSE_BUTTON_ID = 2;

class Button : public BaseObject
{
    private:

        int ID;
        SDL_Point mPosition;
        int posX;
        int posY;
        int hSize;
        int wSize;

    public:
        Button(int ID);
        ~Button();

        void setPos(int x, int y);

        void handleEvent( SDL_Event* e_mouse, bool &menu, bool &state);

        void render(SDL_Renderer *gRenderer);
};

#endif // BUTTON_H
