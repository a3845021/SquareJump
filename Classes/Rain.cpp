#include "Rain.h"
#include "Definitions.h"

USING_NS_CC;

Rain::Rain(Layer *layer) : rainDrops(RAIN_DROPS_NUMBER)
{
    for(int i = 0; i < RAIN_DROPS_NUMBER; ++i)
    {
        auto rainDrop = std::unique_ptr<RainDrop>(new RainDrop(layer, "rainDrop2.png"));
        rainDrops[i] = std::move(rainDrop);
    }
}

void Rain::moveDown(float dt)
{
    CCLOG("%d", rainDrops.capacity());
    for(std::unique_ptr<RainDrop> &rainDrop: rainDrops)
    {
        rainDrop->moveDown(dt);
    }
}
