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
    cocos2d::Sprite *getSprite() const;

//    Triangle(const Triangle& triangle){
//        CCLOG("Copy Constructor %d, %d", triangle.id, this->id);
//    }
//
//    Triangle(Triangle && triangle){
//        CCLOG("Move Constructor %d, %d", triangle.id, this->id);
//    }
//
//    Triangle& operator=(const Triangle& triangle){
//        CCLOG("Copy Assignment %d, %d", triangle.id, this->id);
//    }
//
//    Triangle& operator=(Triangle && triangle){
//        CCLOG("Move Assignment %d, %d", triangle.id, this->id);
//    }

    virtual ~Triangle() { CCLOG("Triangle Destroyed %d", id); };

private:
    void setInitPosition(const cocos2d::Layer *layer);

    int id;

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    ScreenSide screenSide;
    Side side;

    bool used;

    cocos2d::Sprite *triangleSprite;
};


#endif //__TRIANGLE_H__
