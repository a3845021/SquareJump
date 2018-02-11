#include "FlippingSquare.h"
#include "Definitions.h"

USING_NS_CC;

FlippingSquare::FlippingSquare(cocos2d::Layer *layer, const FlippingSquare::ScreenSide &screenSide) {

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    this->screenSide = screenSide;
    side = Side::RIGHT; // square appear on right side of bar
    
    std::string str = "flippingSquare/flippingSquare";

    flippingSquareSprite = Sprite::createWithSpriteFrameName(str + "1.png");

    const auto lineSprite = layer->getChildByName("line");

    setInitPosition(lineSprite);

//    initAnimations(str);

    layer->addChild(flippingSquareSprite);
    
}

void FlippingSquare::setInitPosition(const cocos2d::Node *lineSprite) {
    if(screenSide == ScreenSide::LEFT) {
        flippingSquareSprite->setPosition(Point(
                lineSprite->getPositionX() - (lineSprite->getContentSize().width / 2) -
                        (flippingSquareSprite->getContentSize().width / 2),
                origin.y + visibleSize.height / 2
        ));
    }else if(screenSide == ScreenSide::RIGHT) {
        flippingSquareSprite->setPosition(Point(
//                lineSprite->getPositionX() + (lineSprite->getContentSize().width / 2) +
//                (flippingSquareSprite->getContentSize().width / 2),
                origin.x + visibleSize.width - (flippingSquareSprite->getContentSize().width / 2),
                origin.y + visibleSize.height / 2
        ));
    }
}

void FlippingSquare::flip() {
    int coefSide = (side == Side::LEFT) ? -1 : 1;
    const Node* parentNode = flippingSquareSprite->getParent();
    flippingSquareSprite->stopAllActions();
    flippingSquareSprite->runAction(Spawn::create(
            RotateBy::create(FLIP_ANIMATION_TIME, coefSide * ROTATION_NUMBER * 360),
            MoveBy::create(
                    FLIP_ANIMATION_TIME,
                    Point(
//                            -(parentNode->getChildByName("line")->getContentSize().width +
//                              flippingSquareSprite->getContentSize().width),
                            -coefSide * (origin.x + visibleSize.width / 2 -
                                    parentNode->getChildByName("line")->getContentSize().width / 2 -
                                    flippingSquareSprite->getContentSize().width),
                            0)),
            nullptr));
    side = (side == Side::LEFT) ? Side::RIGHT : Side::LEFT;
}

//
//void FlippingSquare::initAnimations(const std::string &str) {
//    animationsMap.insert("FLIP_RIGHT", getFlipAnimation(str, FLIP_ANIMATION_TIME, 2, 10));
//    animationsMap.insert("FLIP_LEFT", getFlipAnimation(str, FLIP_ANIMATION_TIME, 11, 19));
//}
//
//Animation *FlippingSquare::getFlipAnimation(const std::string &str,
//                                            const float duration,
//                                            const int startFrameNum,
//                                            const int endFrameNum) {
//    auto spriteFrameCache = SpriteFrameCache::getInstance();
//
//    Animation *flipAnimation = Animation::create();
//
//    for(int i = startFrameNum; i <= endFrameNum; ++i)
//    {
//        std::ostringstream fileNameStream;
//        fileNameStream << str << i << ".png";
//        SpriteFrame *frame = spriteFrameCache->getSpriteFrameByName(fileNameStream.str().c_str());
//        flipAnimation->addSpriteFrame(frame);
//    }
//    flipAnimation->setDelayPerUnit(duration / (endFrameNum - startFrameNum + 1));
//    flipAnimation->setRestoreOriginalFrame(true);
//
//    return flipAnimation;
//}

