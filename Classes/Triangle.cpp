#include "Triangle.h"
#include "MyBodyParser.h"
#include "Definitions.h"

USING_NS_CC;

int Triangle::counter = 0;

Triangle::Triangle(Scene *scene, Triangle::ScreenSide screenSide, Triangle::Side side):
        scene(scene), screenSide(screenSide), side(side), used(true), triangleSprite(nullptr) {

    id = counter++;
//    CCLOG("Triangle Created %d", id);
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    triangleSprite = Sprite::createWithSpriteFrameName("triangle1.png");

    MyBodyParser::getInstance()->parseJsonFile("triangleBody.json");

    // triangle related
    const auto triangleBody = MyBodyParser::getInstance()->bodyFormJson(triangleSprite, "triangleBody", PHYSICSBODY_MATERIAL_DEFAULT);
    triangleBody->setCollisionBitmask(TRIANGLE_COLLISION_BITMASK);
    triangleBody->setContactTestBitmask(true);
    triangleBody->setDynamic(false);
    triangleSprite->setPhysicsBody(triangleBody);

    setInitPositionTriangle();

    this->scene->addChild(triangleSprite);
    ////////////////////////////////

    // scoring line related
    scoringLineNode = Node::create();
    const auto lineCenterSprite = this->scene->getChildByName("lineCenter");
    const auto lineLeftSprite = this->scene->getChildByName("lineLeft");
    scoringLineSize = Size(lineCenterSprite->getPositionX() -
            lineCenterSprite->getContentSize().width / 2 - lineLeftSprite->getPositionX() -
            lineLeftSprite->getContentSize().width / 2,
            1.0f);
    const auto scoringLineBody = PhysicsBody::createBox(scoringLineSize);
    scoringLineBody->setCollisionBitmask(SCORING_LINE_COLLISION_BITMASK);
    scoringLineBody->setContactTestBitmask(true);
    scoringLineBody->setDynamic(false);
    scoringLineNode->setPhysicsBody(scoringLineBody);

    setInitPositionScoringLine();

    this->scene->addChild(scoringLineNode);
    ////////////////////////////////
}

void Triangle::setInitPositionTriangle() {
    if(screenSide == ScreenSide::LEFT) {
        if(side == Side::LEFT) {
            const auto lineSprite = scene->getChildByName("lineLeft");
            triangleSprite->setPosition(Point(
                    origin.x + lineSprite->getContentSize().width + triangleSprite->getContentSize().width / 2,
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
            triangleSprite->setScaleX(-1);
        } else if(side == Side::RIGHT) {
            const auto lineSprite = scene->getChildByName("lineCenter");
            triangleSprite->setPosition(Point(
                    lineSprite->getPositionX() - lineSprite->getContentSize().width / 2 -
                    triangleSprite->getContentSize().width / 2,
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
        }
    } else if(screenSide == ScreenSide::RIGHT) {
        if(side == Side::LEFT) {
            const auto lineSprite = scene->getChildByName("lineCenter");
            triangleSprite->setPosition(Point(
                    lineSprite->getPositionX() + lineSprite->getContentSize().width / 2 +
                    triangleSprite->getContentSize().width / 2,
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
            triangleSprite->setScaleX(-1);
        } else if(side == Side::RIGHT) {
            const auto lineSprite = scene->getChildByName("lineRight");
            triangleSprite->setPosition(Point(
                    origin.x + visibleSize.width - lineSprite->getContentSize().width - triangleSprite->getContentSize().width / 2,
                    visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2));
        }
    }
}

void Triangle::setInitPositionScoringLine() {
    scoringLineNode->setPositionY(visibleSize.height + origin.y + triangleSprite->getContentSize().height / 2);
    if(side == Side::LEFT) {
        scoringLineNode->setPositionX(
                triangleSprite->getPositionX() - triangleSprite->getContentSize().width / 2 +
                scoringLineSize.width / 2);
    } else if(side == Side::RIGHT) {
        scoringLineNode->setPositionX(
                triangleSprite->getPositionX() + triangleSprite->getContentSize().width / 2 -
                scoringLineSize.width / 2);
    }
}

void Triangle::moveDown(float dt) {

    if((triangleSprite->getPositionY() + (triangleSprite->getContentSize().height / 2)) > origin.y) {
        triangleSprite->setPositionY(triangleSprite->getPositionY() -
                                    (GAME_SPEED_COEF * visibleSize.height * dt));
        scoringLineNode->setPositionY(scoringLineNode->getPositionY() -
                                    (GAME_SPEED_COEF * visibleSize.height * dt));
    } else {
        triangleSprite->removeFromParent();
        scoringLineNode->removeFromParent();
        used = false;
    }
}

cocos2d::Sprite *Triangle::getTriangleSprite() const {
    return triangleSprite;
}
