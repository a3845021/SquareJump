#ifndef __FLIPPING_SQUARE_H__
#define __FLIPPING_SQUARE_H__

#include "cocos2d.h"

class FlippingSquare {
public:
    enum class ScreenSide {
        LEFT,
        RIGHT
    };

    FlippingSquare(cocos2d::Layer *layer, const FlippingSquare::ScreenSide &screenSide);
    
    void switchSide();

private:
    enum class State {
        LEFT,
        SWITCHING_SIDES,
        RIGHT
    };

    void setInitPosition(const cocos2d::Node *lineSprite);

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    State state;
    ScreenSide screenSide;
    cocos2d::Sprite *flippingSquareSprite;

};
#endif // __FLIPPING_SQUARE_H__


