# BananaKong!

BananaKong! (NOT AUTHENTIC) is a C++ SDL game project for mid term INT2215_2 class of UET-VNU.

## Developer

### Prerequisites
BananaKong! (NOT AUTHENTIC) is a C++ SDL game so SDL library and its support libraries (image, mixer, ttf) are required. It is also recommended that you have git and CodeBlocks 20.03 installed.

### Getting started
- Use git or the download button (on the right) to download the game source code.
- If you are using CodeBlock:
  + Add SDL and its support libraries to CodeBlocks, dependencies are:\
  		[SDL] https://www.libsdl.org/download-2.0.php \
     	[SDL_image] https://www.libsdl.org/projects/SDL_image/ \
     	[SDL_mixer] https://www.libsdl.org/projects/SDL_image/ \
     	[SDL_ttf] https://github.com/libsdl-org/SDL_ttf
  + Run the BananaKong.cbp file with CodeBlocks and compile, the game should start.

### Game Control
- Press start to start play.
- Use Up button or Space Button to jump up, Down button to jump down.
- While the character is not grounded, press and hold Up button or Space button to use the "Parachute"
- The number of bananas you got and running distance are located at the top left corner of the screen.
- Press the pause button at the top left corner to pause the game.

### Graphics/Textures
The game texture (sprite-sheet) and image cutouts (sprites) are packed in `Material`.

### License
- Source codes (except SDL libraries) is writen fully by PhuQuocTrung (https://www.facebook.com/phuquoctrung27).
- SDL librearies is distributed under the zlib license (https://www.libsdl.org/license.php).
- UVN Van Bold font copyrighted by 2001 Tom Truong.
- Nueva Bold Extended Copyrighted by 1994 Adobe Systems Incorporated.
- Background title.png, Paused.png is designed by PhuQuocTrung.
- MainBgm.wav is extracted from original BananaKong! game by FDG Entertainment.
- Other sound effect could be downloaded freely from https://mixkit.co/free-sound-effects/game/
- Other sprites and images could be downloaded freely from https://pngtree.com/.
