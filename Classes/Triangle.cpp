#include "Triangle.h"
#include "MyBodyParser.h"
#include "Definitions.h"

USING_NS_CC;

int Triangle::counter = 0;

Triangle::Triangle(Layer *layer, Triangle::ScreenSide screenSide, Triangle::Side side):
        screenSide(screenSide), side(side), used(true), triangleSprite(nullptr) {

    id = counter++;
//    CCLOG("Triangle Created %d", id);
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    triangleSprite = Sprite::createWithSpriteFrameName("triangle1.png");

    MyBodyParser::getInstance()->parseJsonFile("triangleBody.json");

    //    auto triangleBody = PhysicsBody::createBox(triangleSprite->getContentSize());
    auto triangleBody = MyBodyParser::getInstance()->bodyFormJson(triangleSprite, "triangleBody", PHYSICSBODY_MATERIAL_DEFAULT);
    triangleBody->setCollisionBitmask(TRIANGLE_COLLISION_BITMASK);
    triangleBody->setContactTestBitmask(true);
    triangleBody->setDynamic(false);
    triangleSprite->setPhysicsBody(triangleBody);

    setInitPosition(layer);

    layer->addChild(triangleSprite);
}

void Triangle::setInitPosition(const Layer *layer) {
    if(screenSide == ScreenSide::LEFT) {
        if(side == Side::LEFT) {
            const auto lineSprite = layer->getChildByName("lineLeft");
            triangleSprite->setPosition(Point(
                    origin.x + lineSprite->getContentSize().width + triangleSprite->getContentSize().width / 2,
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
            triangleSprite->setScaleX(-1);
        }else if(side == Side::RIGHT) {
            const auto lineSprite = layer->getChildByName("lineCenter");
            triangleSprite->setPosition(Point(
                    lineSprite->getPositionX() - lineSprite->getContentSize().width / 2 -
                    triangleSprite->getContentSize().width / 2,
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
        }
    }else if(screenSide == ScreenSide::RIGHT) {
        if(side == Side::LEFT) {
            const auto lineSprite = layer->getChildByName("lineCenter");
            triangleSprite->setScaleX(-1);
            triangleSprite->setPosition(Point(
                    lineSprite->getPositionX() + lineSprite->getContentSize().width / 2 +
                    triangleSprite->getContentSize().width / 2,
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
        }else if(side == Side::RIGHT) {
            const auto lineSprite = layer->getChildByName("lineRight");
            triangleSprite->setPosition(Point(
                    origin.x + visibleSize.width - lineSprite->getContentSize().width - triangleSprite->getContentSize().width / 2,
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
        }
    }
}

void Triangle::moveDown(float dt) {

    if((triangleSprite->getPositionY() + (triangleSprite->getContentSize().height / 2)) > origin.y) {
        triangleSprite->setPositionY(triangleSprite->getPositionY() -
                                    (GAME_SPEED_COEF * visibleSize.height * dt));
    }else {
        triangleSprite->removeFromParent();
        used = false;
    }
}

cocos2d::Sprite *Triangle::getTriangleSprite() const {
    return triangleSprite;
}

