#include <iostream>
#include <utility>
#include "RainDrop.h"
#include "Definitions.h"

USING_NS_CC;

RainDrop::RainDrop(Node *rainNode, const std::string &filename, std::pair<float, float> scaleRangePair): scaleRangePair(
        std::move(scaleRangePair)) {
    
    visibleSize = Director::getInstance()->getVisibleSize();

    rainDropSprite = Sprite::createWithSpriteFrameName(filename);
    rainDropSprite->setOpacity(RAIN_DROP_OPACITY);
    setRandomScale();

    rainContentSize = rainNode->getContentSize();
    rainDropSprite->setPosition(Vec2(
                random(
                    rainDropSprite->getBoundingBox().size.width / 2,
                    rainContentSize.width - rainDropSprite->getBoundingBox().size.width / 2),
                random(0.0f, rainContentSize.height)));
    rainNode->addChild(rainDropSprite);
}

void RainDrop::moveDown(float dt) {
    if(isOnScreen()) {
        auto speedCoef = (rainDropSprite->getScale() - MIN_RAIN_DROP_SCALE + (MAX_RAIN_DROP_SCALE - rainDropSprite->getScale()) * RAIN_SPEED_SCALE_COEF) /
                (MAX_RAIN_DROP_SCALE - MIN_RAIN_DROP_SCALE); //min value is 1/2 and max value is 1, direct proportional to scale

        rainDropSprite->setPositionY(rainDropSprite->getPositionY() -
                                     (RAIN_SPEED * speedCoef * visibleSize.height * dt));
    } else {
        resetRainDrop();
    }
}

void RainDrop::setRandomScale() {
    auto randomScale = random(this->scaleRangePair.first, this->scaleRangePair.second);
    rainDropSprite->setScale(randomScale);
}

bool RainDrop::isOnScreen() {
    return (rainDropSprite->getPositionY() + (rainDropSprite->getBoundingBox().size.height / 2)) > 0;
}

void RainDrop::resetRainDrop() {
    setRandomScale();
    rainDropSprite->setPosition(Vec2(
                random(
                    rainDropSprite->getBoundingBox().size.width / 2,
                    rainContentSize.width - rainDropSprite->getBoundingBox().size.width / 2),
                rainContentSize.height + rainDropSprite->getBoundingBox().size.height / 2));
}
