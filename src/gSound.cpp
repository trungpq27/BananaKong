#include "gSound.h"

//----------Declare----------
bool Death_Sound_Played = 0;
Mix_Music *gMusic = NULL;
Mix_Chunk *gBananaGet_Sound = NULL;
Mix_Chunk *gMonkeyJump_Sound = NULL;
Mix_Chunk *gClick_Sound = NULL;
Mix_Chunk *Hover_Sound = NULL;
Mix_Chunk *Death_Sound = NULL;
Mix_Chunk *SeeYa = NULL;


//----------Function----------
void ExitSound(){
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
    Mix_PlayChannel(-1, SeeYa, 0);
    SDL_Delay(1500);
}

//----------LoadMedia----------
bool isLoadSoundOK(){
    bool success = true;

    gMusic = Mix_LoadMUS( "Material/Sound/MainBgm.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gBananaGet_Sound = Mix_LoadWAV( "Material/Sound/BananaGet.wav" );
    if( gBananaGet_Sound == NULL )
    {
        printf( "Failed to load BananaGet effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gMonkeyJump_Sound = Mix_LoadWAV( "Material/Sound/MonkeyJump.wav" );
    if( gBananaGet_Sound == NULL )
    {
        printf( "Failed to load MonkeyJump effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gClick_Sound = Mix_LoadWAV( "Material/Sound/MouseClick.wav" );
    if( gClick_Sound == NULL )
    {
        printf( "Failed to load MouseClick effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    Hover_Sound = Mix_LoadWAV( "Material/Sound/ButtonHover.wav" );
    if( Hover_Sound == NULL )
    {
        printf( "Failed to load ButtonHover effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    Death_Sound = Mix_LoadWAV( "Material/Sound/Death.wav" );
    if( Death_Sound == NULL )
    {
        printf( "Failed to load Death effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    SeeYa = Mix_LoadWAV( "Material/Sound/seeya.wav" );
    if( SeeYa == NULL )
    {
        printf( "Failed to load SeeYa effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void closeSound(){
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk( gBananaGet_Sound );
    Mix_FreeChunk( gMonkeyJump_Sound );
    Mix_FreeChunk( gClick_Sound );
    Mix_FreeChunk( Hover_Sound );
    Mix_FreeChunk( Death_Sound );

    gMusic = NULL;
    gBananaGet_Sound = NULL;
    gMonkeyJump_Sound = NULL;
    gClick_Sound = NULL;
    Hover_Sound = NULL;
    Death_Sound = NULL;
}
