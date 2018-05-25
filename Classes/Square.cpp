#include "Square.h"
#include "Definitions.h"

USING_NS_CC;

Square::Square(cocos2d::Scene *scene, Square::ScreenSide screenSide):
        screenSide(screenSide), squareSprite(nullptr), state(State::RIGHT) {  // square appear on right side of bar

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    squareSprite = Sprite::createWithSpriteFrameName("square.png");
    setInitPosition(scene);

    auto squareBody = PhysicsBody::createBox(squareSprite->getContentSize());
    squareBody->setCollisionBitmask(SQUARE_COLLISION_BITMASK);
    squareBody->setContactTestBitmask(true);
    squareBody->setDynamic(false);

    squareSprite->setPhysicsBody(squareBody);

    scene->addChild(squareSprite);
}

void Square::setInitPosition(cocos2d::Scene *scene) {

    if(screenSide == ScreenSide::LEFT) {
        const auto lineSprite = scene->getChildByName("lineCenter");
        squareSprite->setPosition(Point(
                lineSprite->getPositionX() - lineSprite->getContentSize().width / 2 -
                        squareSprite->getContentSize().width / 2,
                origin.y + visibleSize.height / 2));
    }else if(screenSide == ScreenSide::RIGHT) {
        const auto lineSprite = scene->getChildByName("lineRight");
        squareSprite->setPosition(Point(
                origin.x + visibleSize.width - lineSprite->getContentSize().width - squareSprite->getContentSize().width / 2,
                origin.y + visibleSize.height / 2));
    }
}

void Square::switchSide() {
    const auto initState = state;
    state = State::SWITCHING_SIDES;
    squareSprite->stopAllActions();

    addRotationTrace(initState);

    int coefSide;
    State afterActionState;
    Vec2 movementVec;

    if(initState == State::LEFT) {
        coefSide = 1;
        afterActionState = State::RIGHT;
    } else { //initState == State::RIGHT
        coefSide = -1;
        afterActionState = State::LEFT;
    }

    const auto switchSideCallback = CallFunc::create([=]() {    // = captures object by reference if it exists
                                                                // and all automatic variables used in body of lambda by copy
        state = afterActionState;
        squareSprite->removeAllChildren();
    });

    movementVec = getMovementVec(coefSide);

    squareSprite->runAction(Sequence::create(
            Spawn::create(
                    RotateBy::create(SQUARE_ANIMATION_TIME, coefSide * ROTATION_NUMBER * 360),
                    MoveBy::create(SQUARE_ANIMATION_TIME, movementVec),
                    nullptr),
            switchSideCallback,
            nullptr));
}

bool Square::canSwitchSide() const {
    return state != State::SWITCHING_SIDES;
}

Vec2 Square::getMovementVec(int &coefSide) {
    Vec2 movementVec;
    Node *lineSprite1, *lineSprite2;

    const auto parentNode = squareSprite->getParent();
    if(screenSide == ScreenSide::LEFT) {
        lineSprite1 = parentNode->getChildByName("lineCenter");
        lineSprite2 = parentNode->getChildByName("lineLeft");
    }else { //screenSide == ScreenSide::RIGHT
        lineSprite1 = parentNode->getChildByName("lineRight");
        lineSprite2 = parentNode->getChildByName("lineCenter");
    }

    movementVec.x = coefSide * (lineSprite1->getPositionX() - lineSprite1->getContentSize().width / 2 -
                               lineSprite2->getPositionX() - lineSprite2->getContentSize().width / 2 -
                               squareSprite->getContentSize().width);
    return movementVec;
}

void Square::addRotationTrace(const State &initState) {
    std::string str = "rotationTrace.png"; //need to change
    auto rotationTraceLeft = Sprite::createWithSpriteFrameName(str);
    auto rotationTraceUp = Sprite::createWithSpriteFrameName(str);
    auto rotationTraceRight = Sprite::createWithSpriteFrameName(str);
    auto rotationTraceDown = Sprite::createWithSpriteFrameName(str);
    if(initState != State::LEFT) {
        rotationTraceLeft->setFlippedY(true);
        rotationTraceUp->setFlippedY(true);
        rotationTraceRight->setFlippedY(true);
        rotationTraceDown->setFlippedY(true);
    }
    rotationTraceLeft->setPosition(Point(- rotationTraceLeft->getContentSize().width / 2,
                                         squareSprite->getContentSize().height / 2));

    rotationTraceUp->setPosition(Point( squareSprite->getContentSize().width / 2,
                                        squareSprite->getContentSize().height + rotationTraceUp->getContentSize().width / 2));
    rotationTraceUp->setRotation(90.0f);

    rotationTraceRight->setPosition(Point(squareSprite->getContentSize().width + rotationTraceRight->getContentSize().width / 2,
                                          squareSprite->getContentSize().height / 2));
    rotationTraceRight->setRotation(180.0f);

    rotationTraceDown->setPosition(Point(squareSprite->getContentSize().width / 2,
                                         - rotationTraceDown->getContentSize().width / 2));
    rotationTraceDown->setRotation(270.0f);

    squareSprite->addChild(rotationTraceLeft);
    squareSprite->addChild(rotationTraceUp);
    squareSprite->addChild(rotationTraceRight);
    squareSprite->addChild(rotationTraceDown);
}
