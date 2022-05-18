#ifndef GTEXT_H
#define GTEXT_H

#include "BaseObj.h"
#include "BaseFunc.h"

const string fontPath = "Material/Fonts/Nueva.ttf";
const SDL_Color ScoreColor = { 	203, 134, 65 };
const SDL_Color ScoreBorderColor = { 41, 51, 33 };
const SDL_Color DeathScoreColor = {142, 50, 0 };
const SDL_Color DeathScoreBorderColor = {0, 0, 0 };


class gText : public BaseObject{
    private:
        SDL_Texture* gFontTexture;
        int textWidth;
        int textHeight;
        int centeredPosX;

    public:
        gText();

        ~gText();

        void free();

		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font *gFont);

		int getCenter();

		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void setBlendMode( SDL_BlendMode blending );

		void setAlpha( Uint8 alpha );

		void render(int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

};

//-----Declare-----
extern TTF_Font *gFont;
extern TTF_Font *gBorderFont;
extern TTF_Font *gDeathFont;
extern TTF_Font *gDeathBorderFont;

extern gText gTextTexture;

//-----Function-----
void RenderScoreWithPosY(string Message, int PosY);

//-----Load Media-----
extern bool isLoadTextOK();
extern void closeText();

#endif // GTEXT_H
