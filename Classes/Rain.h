#ifndef __RAIN_H__
#define __RAIN_H__

#include "cocos2d.h"
#include "RainDrop.h"

class Rain 
{
public:
    Rain(cocos2d::Layer *layer);
    ~Rain();
    void moveDown(float dt);

private:
    std::vector<std::unique_ptr<RainDrop>> rainDrops;

};
#endif // __RAIN_H__
