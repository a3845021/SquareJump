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
    Rain *rain;
    Line *line;
    FlippingSquare *flippingSquare;
};

#endif // __GAME_SCENE_H__
