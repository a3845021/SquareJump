#include "FlippingSquare.h"
#include "Definitions.h"

USING_NS_CC;

FlippingSquare::FlippingSquare(cocos2d::Layer *layer, const FlippingSquare::ScreenSide &screenSide) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    this->screenSide = screenSide;
    state = State::RIGHT; // square appear on right side of bar
    
    std::string str = "flippingSquare/flippingSquare";

    flippingSquareSprite = Sprite::createWithSpriteFrameName(str + "1.png");

    const auto lineSprite = layer->getChildByName("line");

    setInitPosition(lineSprite);

    layer->addChild(flippingSquareSprite);
    
}

void FlippingSquare::setInitPosition(const cocos2d::Node *lineSprite) {
    if(screenSide == ScreenSide::LEFT) {
        flippingSquareSprite->setPosition(Point(
                lineSprite->getPositionX() - (lineSprite->getContentSize().width / 2) -
                        (flippingSquareSprite->getContentSize().width / 2),
                origin.y + visibleSize.height / 2));
    }else if(screenSide == ScreenSide::RIGHT) {
        flippingSquareSprite->setPosition(Point(
                origin.x + visibleSize.width - (flippingSquareSprite->getContentSize().width / 2),
                origin.y + visibleSize.height / 2));
    }
}

void FlippingSquare::switchSide() {
    if(state!=State::SWITCHING_SIDES) { //if switching do nothing
        const int coefSide = (state == State::LEFT) ? 1 : -1;
        const State afterActionState = (state == State::LEFT) ? State::RIGHT : State::LEFT;
        state = State::SWITCHING_SIDES;
        const auto switchSideCallback = CallFunc::create([=]() {    // = captures object by reference if it exists
                                                                    // and all automatic variables used in body of lambda by copy
            state = afterActionState;
        });

        const Node *parentNode = flippingSquareSprite->getParent();
        flippingSquareSprite->stopAllActions();
        flippingSquareSprite->runAction(Sequence::create(
                Spawn::create(
                        RotateBy::create(FLIP_ANIMATION_TIME, coefSide * ROTATION_NUMBER * 360),
                        MoveBy::create(
                                FLIP_ANIMATION_TIME,
                                Point(
                                        coefSide * (visibleSize.width / 2 -
                                                parentNode->getChildByName("line")->getContentSize().width / 2 -
                                                flippingSquareSprite->getContentSize().width),
                                        0)),
                        nullptr),
                switchSideCallback,
                nullptr));
    }
}