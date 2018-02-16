#ifndef __RAIN_DROP_H__
#define __RAIN_DROP_H__

#include "cocos2d.h"

class RainDrop {
public:
    RainDrop(cocos2d::Layer *layer, const std::string& filename, const float scale);

    void moveDown(float dt);

private:
    bool isOnScreen();

    void resetRainDrop();

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite *rainDropSprite;
};
#endif // __RAIN_DROP_H__

