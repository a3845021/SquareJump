#include "Triangle.h"
#include "Definitions.h"

USING_NS_CC;

int Triangle::counter = 0;

Triangle::Triangle(cocos2d::Layer *layer, Triangle::ScreenSide screenSide, Triangle::Side side):
        screenSide(screenSide), side(side), used(true), triangleSprite(nullptr) {

    id = counter++;
    CCLOG("Triangle Created %d", id);
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    triangleSprite = Sprite::createWithSpriteFrameName("triangle.png");

    setInitPosition(layer);

    layer->addChild(triangleSprite);
}

void Triangle::setInitPosition(const cocos2d::Layer *layer) {
    const auto lineSprite = layer->getChildByName("line");
    const auto rotation = -180.0f;
    if(screenSide == ScreenSide::LEFT) {
        if(side == Side::LEFT) {
            triangleSprite->setPosition(Point(
                    origin.x + triangleSprite->getContentSize().width / 2,
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
        }else if(side == Side::RIGHT) {
            triangleSprite->setRotation(rotation);
            triangleSprite->setPosition(Point(
                    lineSprite->getPositionX() - (lineSprite->getContentSize().width / 2) -
                    (triangleSprite->getContentSize().width / 2),
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
        }
    }else if(screenSide == ScreenSide::RIGHT) {
        if(side == Side::LEFT) {
            triangleSprite->setPosition(Point(
                    lineSprite->getPositionX() + (lineSprite->getContentSize().width / 2) +
                    (triangleSprite->getContentSize().width / 2),
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
        }else if(side == Side::RIGHT) {
            triangleSprite->setRotation(rotation);
            triangleSprite->setPosition(Point(
                    origin.x + visibleSize.width - (triangleSprite->getContentSize().width / 2),
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
        }
    }
}

void Triangle::moveDown(float dt) {
//    distanceTillNextTriangle -= TRIANGLE_SPEED * visibleSize.height * dt;

    if((triangleSprite->getPositionY() + (triangleSprite->getContentSize().height / 2)) > origin.y) {
        triangleSprite->setPositionY(triangleSprite->getPositionY() -
                                    (TRIANGLE_SPEED * visibleSize.height * dt));
    }else {
        triangleSprite->removeFromParent();
        used = false;
//        triangleSprite->setPositionY(visibleSize.height + origin.y +
//                                    (triangleSprite->getContentSize().height / 2));
    }
}

cocos2d::Sprite *Triangle::getSprite() const {
    return triangleSprite;
}

