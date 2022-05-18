#include "gText.h"


//----------Object Class----------
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

bool gText::loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font *gFont)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderUTF8_Blended( gFont, textureText.c_str(), textColor );
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
    int w, h;
    if (TTF_SizeText(gFont, textureText.c_str(), &w, &h)){
        printf( "Unable to get text size! SDL Error: %s\n", SDL_GetError() );
    }
    else centeredPosX = (SCREEN_WIDTH - w)/2;
	//cout << centeredPosX << "\n";   //debug only

	//Return success
	return gFontTexture != NULL;
}

int gText::getCenter(){
    return centeredPosX;
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

void gText::render(int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, textWidth, textHeight };

	SDL_RenderCopyEx( gRenderer, gFontTexture, NULL, &renderQuad, angle, center, flip );
}


//---------Declare----------
TTF_Font *gFont = NULL;
TTF_Font *gBorderFont = NULL;
TTF_Font *gDeathFont = NULL;
TTF_Font *gDeathBorderFont = NULL;

gText gTextTexture;

//----------Function----------
void RenderScoreWithPosY(string Message, int PosY){
    gTextTexture.loadFromRenderedText( Message, DeathScoreBorderColor, gDeathBorderFont);
    gTextTexture.render(gTextTexture.getCenter(), PosY);
    gTextTexture.loadFromRenderedText( Message, DeathScoreColor, gDeathFont);
    gTextTexture.render(gTextTexture.getCenter(), PosY);
}


//----------Load Media----------
bool isLoadTextOK(){
    bool success = true;
    gFont = TTF_OpenFont( "Material/Fonts/UVNVan.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	gBorderFont = TTF_OpenFont( "Material/Fonts/UVNVan.ttf", 28 );
	if( gBorderFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	gDeathFont = TTF_OpenFont( "Material/Fonts/Nueva.ttf", 40 );
	if( gDeathFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	gDeathBorderFont = TTF_OpenFont( "Material/Fonts/Nueva.ttf", 40 );
	if( gDeathBorderFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else TTF_SetFontOutline(gDeathBorderFont, 1);
	return success;
}

void closeText(){
    gTextTexture.free();
}
