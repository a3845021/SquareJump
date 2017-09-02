#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();

    scene->addChild(layer);

    return scene; 
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("gameSpriteSheet.plist");

    auto backgroundSprite = Sprite::createWithSpriteFrameName("background.png");               
    backgroundSprite->setPosition(Point(                                    
                visibleSize.width / 2 + origin.x,                           
                visibleSize.height / 2 + origin.y));                        
                                                                            
    this->addChild(backgroundSprite);
    
    rain = new Rain(this);

    line = new Line(this);
    
    flippingSquare = new FlippingSquare(this);
    //flippingSquare->flip();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->
        addEventListenerWithSceneGraphPriority(touchListener, this);

    this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt)
{
    //CCLOG("%f", dt);
    rain->moveDown(dt);
    line->moveDown(dt);
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    CCLOG("TouchBegan");
    flippingSquare->flip();

    return true;
}
