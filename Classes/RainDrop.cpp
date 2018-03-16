#include <iostream>
#include <utility>
#include "RainDrop.h"
#include "Definitions.h"

USING_NS_CC;

RainDrop::RainDrop(Layer *layer, const std::string &filename, std::pair<float, float> scaleRangePair): scaleRangePair(
        std::move(scaleRangePair)) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
   
    rainDropSprite = Sprite::createWithSpriteFrameName(filename);
    rainDropSprite->setOpacity(RAIN_DROP_OPACITY);
    setRandomScale();
    rainDropSprite->setPosition(Point(
                random(origin.x + (rainDropSprite->getBoundingBox().size.width / 2),
                        visibleSize.width + origin.x - (rainDropSprite->getBoundingBox().size.width / 2)),
                random(origin.y,
                        visibleSize.height + origin.y)));
    layer->addChild(rainDropSprite);
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
    return (rainDropSprite->getPositionY() + (rainDropSprite->getBoundingBox().size.height / 2)) > origin.y;
}

void RainDrop::resetRainDrop() {
    setRandomScale();
    rainDropSprite->setPosition(Point(
                random(
                    origin.x + (rainDropSprite->getBoundingBox().size.width / 2), 
                    visibleSize.width + origin.x - (rainDropSprite->getBoundingBox().size.width / 2)),
                visibleSize.height + origin.y + (rainDropSprite->getBoundingBox().size.height / 2)));
}
