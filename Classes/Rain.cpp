#include "Rain.h"
#include "Definitions.h"

USING_NS_CC;

Rain::Rain(Layer *layer)
{
    for(int i = 0; i < RAIN_DROPS_NUMBER; ++i)
        rainDrops.emplace_back(RainDrop(layer, "rainDrop.png"));
}

void Rain::moveDown(float dt)
{
    //CCLOG("%d", rainDrops.capacity());
    for(auto rainDrop: rainDrops)
        rainDrop.moveDown(dt);
}
