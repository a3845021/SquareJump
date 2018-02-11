#ifndef __FLIPPING_SQUARE_H__
#define __FLIPPING_SQUARE_H__

#include "cocos2d.h"

class FlippingSquare
{
public:
    enum class ScreenSide
    {
        LEFT,
        RIGHT
    };

    FlippingSquare(cocos2d::Layer *layer, const FlippingSquare::ScreenSide &screenSide);
    
    void flip();

private:
    enum class Side
    {
        LEFT,
        RIGHT
    };

//    void initAnimations(const std::string& str);
//    cocos2d::Animation *getFlipAnimation(const std::string &str,
//                                         const float duration,
//                                         const int startFrameNum,
//                                         const int endFrameNum);
    void setInitPosition(const cocos2d::Node *lineSprite);

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    Side side;
    ScreenSide screenSide;
    cocos2d::Sprite *flippingSquareSprite;
    cocos2d::Map<std::string, cocos2d::Animation*> animationsMap;

};
#endif // __FLIPPING_SQUARE_H__


