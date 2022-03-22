#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "BaseFunc.h"
#include "BaseObj.h"

const int STONE_PIG_HEIGH = 370;
const int STONE_PIG_WIDTH = STONE_PIG_HEIGH*1.75;


class Obstacle : public BaseObject
{
    private:
    int posX;
    int posY;

    public:
        Obstacle();
        ~Obstacle();
};

#endif // OBSTACLE_H
