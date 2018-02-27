#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "cocos2d.h"

class Triangle {
public:
    enum class ScreenSide {
        LEFT,
        RIGHT
    };

    enum class Side {
        LEFT,
        RIGHT
    };

    Triangle(cocos2d::Layer *layer, ScreenSide screenSide, Side side);
    void moveDown(float dt);

private:

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    ScreenSide screenSide;
    Side side;

    cocos2d::Sprite *triangleSprite;
};


#endif //__TRIANGLE_H__
