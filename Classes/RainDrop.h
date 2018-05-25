#ifndef __RAIN_DROP_H__
#define __RAIN_DROP_H__

#include "cocos2d.h"

class RainDrop {
public:
    RainDrop(cocos2d::Scene *scene, const std::string& filename, std::pair<float, float> scaleRangePair);

    void moveDown(float dt);

private:
    void setRandomScale();

    bool isOnScreen();

    void resetRainDrop();

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite *rainDropSprite;

    std::pair<float, float> scaleRangePair;
};
#endif // __RAIN_DROP_H__
