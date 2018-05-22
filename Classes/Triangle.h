#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "cocos2d.h"

class Triangle {
public:
    static int counter;
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
    bool inUse () const { return used;};
    cocos2d::Sprite *getTriangleSprite() const;

    virtual ~Triangle() { /*CCLOG("Triangle Destroyed %d", id); */};

private:
    void setInitPositionTriangle();
    void setInitPositionScoringLine();

    int id;

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    ScreenSide screenSide;
    Side side;

    bool used;

    cocos2d::Size scoringLineSize;
    cocos2d::Layer *layer;
    cocos2d::Sprite *triangleSprite;
    cocos2d::Node *scoringLineNode;
};


#endif //__TRIANGLE_H__
