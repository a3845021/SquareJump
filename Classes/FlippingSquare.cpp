#include "FlippingSquare.h"
#include "Definitions.h"

USING_NS_CC;

FlippingSquare::FlippingSquare(cocos2d::Layer *layer)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    side = Side::RIGHT; // square appear on right side of bar
    
    std::string str = "flippingSquare/flippingSquare";

    flippingSquareSprite = Sprite::createWithSpriteFrameName(str + "1.png");

    auto lineSprite = layer->getChildByName("line");

    flippingSquareSprite->setPosition(Point(
               lineSprite->getPositionX() + (lineSprite->getContentSize().width / 2) +
                    (flippingSquareSprite->getContentSize().width / 2),
               origin.y + visibleSize.height / 2
                )); 

    initAnimations(str);

    layer->addChild(flippingSquareSprite);
    
}

void FlippingSquare::flip()
{
    const Node* parentNode = flippingSquareSprite->getParent();
    switch(side)
    {
        case Side::LEFT:
            flippingSquareSprite->stopAllActions();
            flippingSquareSprite->runAction(Spawn::create(
                        Animate::create(animationsMap.at("FLIP_RIGHT")),
                        MoveBy::create(
                            FLIP_ANIMATION_TIME, 
                            Point(
                                parentNode->getChildByName("line")->getContentSize().width +
                                    flippingSquareSprite->getContentSize().width,
                                0)),
                        nullptr));
            side = Side::RIGHT;
            break;
        case Side::RIGHT:
            flippingSquareSprite->stopAllActions();
            flippingSquareSprite->runAction(Spawn::create(
                        Animate::create(animationsMap.at("FLIP_LEFT")),
                        MoveBy::create(
                            FLIP_ANIMATION_TIME, 
                            Point(
                                -(parentNode->getChildByName("line")->getContentSize().width +
                                    flippingSquareSprite->getContentSize().width),
                                0)),
                        nullptr));
            side = Side::LEFT;
            break;
    }
}

void FlippingSquare::initAnimations(const std::string &str)
{
    animationsMap.insert("FLIP_RIGHT", getFlipAnimation(str, FLIP_ANIMATION_TIME, 2, 6));
    animationsMap.insert("FLIP_LEFT", getFlipAnimation(str, FLIP_ANIMATION_TIME, 7, 11));
}

Animation *FlippingSquare::getFlipAnimation(const std::string &str,
                                            const float duration,
                                            const int startFrameNum,
                                            const int endFrameNum)
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();

    Animation *flipAnimation = Animation::create();

    for(int i = startFrameNum; i <= endFrameNum; ++i)
    {
        std::ostringstream fileNameStream;
        fileNameStream << str << i << ".png";
        SpriteFrame *frame = spriteFrameCache->getSpriteFrameByName(fileNameStream.str().c_str());
        flipAnimation->addSpriteFrame(frame);
    }
    flipAnimation->setDelayPerUnit(duration / (endFrameNum - startFrameNum + 1));
    flipAnimation->setRestoreOriginalFrame(true);

    return flipAnimation;
}

