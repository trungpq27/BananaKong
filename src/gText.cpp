#include "gText.h"

gText::gText() : BaseObject::BaseObject(){

}

gText::~gText() {
    free();
}

void gText::free(){
    BaseObject::free();
	if( gFontTexture != NULL )
	{
		SDL_DestroyTexture( gFontTexture );
		gFontTexture = NULL;
		textWidth = 0;
		textHeight = 0;
	}
}

bool gText::loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer *gRenderer )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        gFontTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( gFontTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			textWidth = textSurface->w;
			textHeight = textSurface->h;
		}
		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return gFontTexture != NULL;
}

void gText::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( gFontTexture, red, green, blue );
}

void gText::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( gFontTexture, blending );
}

void gText::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( gFontTexture, alpha );
}

void gText::render( SDL_Renderer *gRenderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, textWidth, textHeight };

	SDL_RenderCopyEx( gRenderer, gFontTexture, NULL, &renderQuad, angle, center, flip );
}
