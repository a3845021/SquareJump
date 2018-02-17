#ifndef __RAIN_H__
#define __RAIN_H__

#include "cocos2d.h"
#include "RainDrop.h"

class Rain {
public:
    explicit Rain(cocos2d::Layer *layer);
    void moveDown(float dt);

private:
    std::map<std::pair<float, float>, int> getScaleRangeMap();

    std::vector<RainDrop> rainDrops;
};
#endif // __RAIN_H__
