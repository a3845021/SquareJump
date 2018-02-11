#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Rain.h"
#include "Line.h"
#include "FlippingSquare.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    void update(float dt);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    const cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    const cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    Rain *rain;
    Line *line;
    std::map<FlippingSquare::ScreenSide, FlippingSquare> flippingSquares;
};

#endif // __GAME_SCENE_H__
