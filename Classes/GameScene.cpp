#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameScene::create();

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
    spriteCache->addSpriteFramesWithFile("gameSpriteSheet.plist");

    auto backgroundSprite = Sprite::createWithSpriteFrameName("background.png");               
    backgroundSprite->setPosition(Point(                                    
                visibleSize.width / 2 + origin.x,                           
                visibleSize.height / 2 + origin.y));                        
                                                                            
    this->addChild(backgroundSprite);

    rain = std::make_unique<Rain>(this);

    line = std::make_unique<Line>(this);

//    triangle = std::make_unique<Triangle>(this, Triangle::ScreenSide::LEFT, Triangle::Side::LEFT);
//    triangles.emplace_back(this, Triangle::ScreenSide::LEFT, Triangle::Side::LEFT);
//    Triangle::distanceTillNextTriangle = TRIANGLE_SPEED * Director::getInstance()->getVisibleSize().height;
    triangleManager = std::make_unique<TriangleManager>(this);

    squaresMap.emplace(std::piecewise_construct,
                       std::forward_as_tuple(Square::ScreenSide::LEFT),
                       std::forward_as_tuple(this, Square::ScreenSide::LEFT));
    squaresMap.emplace(std::piecewise_construct,
                       std::forward_as_tuple(Square::ScreenSide::RIGHT),
                       std::forward_as_tuple(this, Square::ScreenSide::RIGHT));

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->
        addEventListenerWithSceneGraphPriority(touchListener, this);

    this->scheduleUpdate();

    return true;
}

void GameScene::update(float dt) {
    rain->moveDown(dt);
    line->moveDown(dt);

//    for(auto &triangle: triangles) {
//        triangle.moveDown(dt);
//    }
//
////    triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
////                                   [](const Triangle &triangle) { return !triangle.inUse(); }),
////                    triangles.end());
//
//    if(!triangles.empty()) {
//        if(!triangles.front().inUse()) {
//            triangles.pop_front();
//        }
//    }
//
//    Triangle::distanceTillNextTriangle -= TRIANGLE_SPEED * visibleSize.height * dt;
//
//    if(Triangle::distanceTillNextTriangle < 0) {
//        triangles.emplace_back(this, Triangle::ScreenSide::LEFT, Triangle::Side::LEFT);
//    }
    triangleManager->createAndMoveTriangles(dt);
}


bool GameScene::onTouchBegan(Touch *touch, Event *event) {
    Vec2 touchLocation = this->convertTouchToNodeSpace(touch);
    if(touchLocation.x < visibleSize.width / 2 + origin.x) { //check left or right side of the screen
        squaresMap.at(Square::ScreenSide::LEFT).switchSide();
    }else{
        squaresMap.at(Square::ScreenSide::RIGHT).switchSide();
    }
    return true;
}
