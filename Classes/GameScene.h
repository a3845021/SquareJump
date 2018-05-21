#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Rain.h"
#include "Line.h"
#include "Square.h"
#include "Triangle.h"
#include "TriangleManager.h"

class GameScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world;};
    void update(float dt) override;
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    const cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    const cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    cocos2d::PhysicsWorld *sceneWorld = nullptr;
    cocos2d::Label *scoreLabel;

    int score;
    std::unique_ptr<Rain> rain;
    std::vector<Line> lines;
    std::unique_ptr<TriangleManager> triangleManager;
    std::map<Square::ScreenSide, Square> squaresMap;
};

#endif // __GAME_SCENE_H__
