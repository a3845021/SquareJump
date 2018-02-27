#include "Triangle.h"
#include "Definitions.h"

USING_NS_CC;

Triangle::Triangle(cocos2d::Layer *layer, Triangle::ScreenSide screenSide, Triangle::Side side):
        screenSide(screenSide), side(side), triangleSprite(nullptr) {

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    triangleSprite = Sprite::createWithSpriteFrameName("triangle.png");
    triangleSprite->setPosition(Point(
            origin.x + triangleSprite->getContentSize().width / 2,
            visibleSize.height + origin.y - triangleSprite->getContentSize().height / 2));

    layer->addChild(triangleSprite);
}

void Triangle::moveDown(float dt) {
    if((triangleSprite->getPositionY() + (triangleSprite->getContentSize().height / 2)) > origin.y) {
        triangleSprite->setPositionY(triangleSprite->getPositionY() -
                                    (TRIANGLE_SPEED * visibleSize.height * dt));
    }else {
        triangleSprite->setPositionY(visibleSize.height + origin.y +
                                    (triangleSprite->getContentSize().height / 2));
    }
}

