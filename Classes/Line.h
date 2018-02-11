#ifndef __LINE_H__
#define __LINE_H__

#include "cocos2d.h"

class Line {
public:
    Line(cocos2d::Layer *layer);
    void moveDown(float dt);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite *shiningSprite;
};
#endif // __LINE_H__ 
