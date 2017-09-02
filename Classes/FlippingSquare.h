#ifndef __FLIPPING_SQUARE_H__
#define __FLIPPING_SQUARE_H__

#include "cocos2d.h"

class FlippingSquare
{
public:
    FlippingSquare(cocos2d::Layer *layer);
    
    void flip();

private:
    enum class Side
    {
        LEFT,
        RIGHT
    };

    void initAnimations(const std::string& str);
    cocos2d::Animation *getFlipAnimation(const std::string &str,
                                         const float duration,
                                         const int startFrameNum,
                                         const int endFrameNum);

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    Side side;
    cocos2d::Sprite *flippingSquareSprite;
    cocos2d::Map<std::string, cocos2d::Animation*> animationsMap;

};
#endif // __FLIPPING_SQUARE_H__


