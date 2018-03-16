#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "cocos2d.h"

class Square {
public:
    enum class ScreenSide {
        LEFT,
        RIGHT
    };

    Square(cocos2d::Layer *layer, Square::ScreenSide screenSide);

    void switchSide();
    bool canSwitchSide() const;

private:
    enum class State {
        LEFT,
        SWITCHING_SIDES,
        RIGHT
    };

    void setInitPosition(cocos2d::Layer *layer);
    cocos2d::Vec2 getMovementVec(int &coefSide);
    void addRotationTrace(const State &initState);

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    State state;
    ScreenSide screenSide;
    cocos2d::Sprite *squareSprite;

};
#endif // __SQUARE_H__


