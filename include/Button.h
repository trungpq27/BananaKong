#ifndef BUTTON_H
#define BUTTON_H

#include "BaseFunc.h"
#include "BaseObj.h"
#include "gSound.h"

const int START_BUTTON_HEIGHT = 180;
const int START_BUTTON_WIDTH = START_BUTTON_HEIGHT * 1.936;

const int SMALL_BUTTON_HEIGHT = 40;
const int SMALL_BUTTON_WIDTH = SMALL_BUTTON_HEIGHT;

const int ROUND_BUTTON_SIZE = 180;

class Button : public BaseObject
{
    private:
        SDL_Point mPosition;
        bool hover;
        int posX;
        int posY;
        int hSize;
        int wSize;
        int oldW;
        int oldH;

    public:
        Button();
        ~Button();

        void setSize(int wSize, int hSize);

        void setPos(int x, int y);

        void handleEvent( SDL_Event* e_mouse, bool &menu, bool &state);

        void render();
};

//-----Declare-----
extern Button StartButton;
extern Button ExitButton;
extern Button AgainButton;

extern Button PlayButton;
extern Button PauseButton;
extern Button RoundExitButton;
extern Button HomeButton;

//-----Load Media-----
extern bool isLoadButtonOK();
extern void closeButton();

#endif // BUTTON_H
