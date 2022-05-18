#ifndef GSOUND_H
#define GSOUND_H

#include "BaseFunc.h"

//-----Declare-----
extern bool Death_Sound_Played;
extern Mix_Music *gMusic;
extern Mix_Chunk *gBananaGet_Sound;
extern Mix_Chunk *gMonkeyJump_Sound;
extern Mix_Chunk *gClick_Sound;
extern Mix_Chunk *Hover_Sound;
extern Mix_Chunk *Death_Sound;
extern Mix_Chunk *SeeYa;

//-----Function-----

void ExitSound();

//-----Load Media-----
extern bool isLoadSoundOK();
extern void closeSound();

#endif // GSOUND_H
