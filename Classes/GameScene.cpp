#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene() {
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene; 
}

// on "init" you need to initialize your instance
bool GameScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("gameSceneSpriteSheet.plist");

    auto backgroundSprite = Sprite::createWithSpriteFrameName("backgroundGameScene.png");
    backgroundSprite->setPosition(Point(                                    
                visibleSize.width / 2 + origin.x,                           
                visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    rain = std::make_unique<Rain>(this);

    lines.emplace_back(this, "lineCenter");
    lines.back().setPositionX(visibleSize.width / 2 + origin.x);

    lines.emplace_back(this, "lineLeft");
    lines.back().setPositionX(origin.x + lines.back().getLineSprite()->getContentSize().width / 2);

    lines.emplace_back(this, "lineRight");
    lines.back().setPositionX(origin.x + visibleSize.width - lines.back().getLineSprite()->getContentSize().width / 2);

    triangleManager = std::make_unique<TriangleManager>(this);

    squaresMap.emplace(std::piecewise_construct,
                       std::forward_as_tuple(Square::ScreenSide::LEFT),
                       std::forward_as_tuple(this, Square::ScreenSide::LEFT));
    squaresMap.emplace(std::piecewise_construct,
                       std::forward_as_tuple(Square::ScreenSide::RIGHT),
                       std::forward_as_tuple(this, Square::ScreenSide::RIGHT));

    score = 0;
    scoreLabel = Label::createWithTTF(StringUtils::toString(score), MAIN_FONT, visibleSize.height * SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(
            visibleSize.width * 0.75 + origin.x,
            visibleSize.height * 0.75 + origin.y);
    this->addChild(scoreLabel);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->
        addEventListenerWithSceneGraphPriority(touchListener, this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->
        addEventListenerWithSceneGraphPriority(contactListener, this);

    this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt) {
    rain->moveDown(dt);
    for(auto &line: lines) {
        line.moveDown(dt);
    }
    triangleManager->createAndMoveTriangles(dt);
}


bool GameScene::onTouchBegan(Touch *touch, Event *event) {
    Vec2 touchLocation = this->convertTouchToNodeSpace(touch);
    if(touchLocation.x < visibleSize.width / 2 + origin.x) { //check left or right side of the screen
        if(squaresMap.at(Square::ScreenSide::LEFT).canSwitchSide())
            squaresMap.at(Square::ScreenSide::LEFT).switchSide();
    }else{
        if(squaresMap.at(Square::ScreenSide::RIGHT).canSwitchSide())
            squaresMap.at(Square::ScreenSide::RIGHT).switchSide();
    }
    return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if((a->getCollisionBitmask() == TRIANGLE_COLLISION_BITMASK && b->getCollisionBitmask() == SQUARE_COLLISION_BITMASK) ||
            (a->getCollisionBitmask() == SQUARE_COLLISION_BITMASK && b->getCollisionBitmask() == TRIANGLE_COLLISION_BITMASK)) {
        CCLOG("Contact");
    }

    return true;
}
