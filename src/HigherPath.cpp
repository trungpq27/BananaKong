#include "HigherPath.h"

HigherPath::HigherPath() : BaseObject(){
}

HigherPath::~HigherPath(){
    BaseObject::free();
    posX = 0;
    posY = 0;
    ID = 0;
    pathWidth = 0;
}

void HigherPath::init(int ID){

    this->ID = ID;
    if (ID == UP_PATH1_ID){
        pathWidth = UP_PATH1_WIDTH;
        posY = HIGH_PATH_X1_POSY;
    }

    if (ID == UP_PATH2_ID){
        pathWidth = UP_PATH2_WIDTH;
        posY = HIGH_PATH_X1_POSY;
    }

    if (ID == AIR_PATH1_ID){
        pathWidth = AIR_PATH1_WIDTH;
        posY = HIGH_PATH_X2_POSY;
    }
    if (ID == AIR_PATH2_ID){

        pathWidth = AIR_PATH2_WIDTH;
        posY = HIGH_PATH_X2_POSY;
    }
    updateX();

}

void HigherPath::updateX(){

    posX = rand() % (PATH_SCREEN_SPACING) + SCREEN_WIDTH;
    double posX_End = posX + pathWidth;

    int ID_Col = (ID == 1 || ID == 3) ? ID - 1 : ID + 1;

    double OldPosX = PathPosX_Carry[ID_Col];
    double OldPosX_End = OldPosX + PATH_WIDTH[ID_Col];

    if ((posX >= OldPosX && posX <= OldPosX_End)
        || (posX <= OldPosX && posX_End >= OldPosX)){
         posX = OldPosX_End + PATH_SCREEN_SPACING + (rand() % PATH_SCREEN_SPACING);
         posX_End = posX + pathWidth;
    }

    PathPosX_Carry[ID] = posX;
}

void HigherPath::render(int wSize, int hSize){
    BaseObject::render(posX, posY, wSize, hSize);
}

void HigherPath::Move(){

    posX -= MONKEY_RUNNING_SPEED;
    PathPosX_Carry[ID] -= MONKEY_RUNNING_SPEED;
    if(posX < -pathWidth) updateX();
}

double HigherPath::getPosX(){
    return posX;
}

double HigherPath::getPosY(){
    return posY;
}

//----------Declare----------
HigherPath AirPath1_Texture;
HigherPath AirPath2_Texture;
HigherPath UpPath1_Texture;
HigherPath UpPath2_Texture;
double PathPosX_Carry[HIGHER_PATH_COUNT];

//----------Function----------
void MoveAndRenderHigherPath(){
    UpPath1_Texture.Move();
    UpPath1_Texture.render(UP_PATH1_WIDTH, UP_PATH1_HEIGHT);

    UpPath2_Texture.Move();
    UpPath2_Texture.render(UP_PATH2_WIDTH, UP_PATH2_HEIGHT);

    AirPath1_Texture.Move();
    AirPath1_Texture.render(AIR_PATH1_WIDTH, AIR_PATH1_HEIGHT);

    AirPath2_Texture.Move();
    AirPath2_Texture.render(AIR_PATH2_WIDTH, AIR_PATH2_HEIGHT);
}

//----------Load Media----------
bool isLoadHigherPathOK(){
    bool success = true;
    if (!AirPath1_Texture.loadFromFile("Material/HigherPath/AirPath1.png")){
        printf( "Failed to load Ground AirPath1 image!\n" );
        success = false;
    }
    if (!AirPath2_Texture.loadFromFile("Material/HigherPath/AirPath2.png")){
        printf( "Failed to load Ground AirPath2 image!\n" );
        success = false;
    }
    if (!UpPath1_Texture.loadFromFile("Material/HigherPath/UpPath1.png")){
        printf( "Failed to load Ground UpPath1 image!\n" );
        success = false;
    }
    if (!UpPath2_Texture.loadFromFile("Material/HigherPath/UpPath2.png")){
        printf( "Failed to load Ground UpPath2 image!\n" );
        success = false;
    }
    return success;
}

void closeHigherPath(){
    AirPath1_Texture.free();
    AirPath2_Texture.free();
    UpPath1_Texture.free();
    UpPath2_Texture.free();
}
