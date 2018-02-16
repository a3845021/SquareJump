#include <iostream>
#include "RainDrop.h"
#include "Definitions.h"

USING_NS_CC;

RainDrop::RainDrop(Layer *layer, const std::string& filename, const float scale) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
   
    rainDropSprite = Sprite::createWithSpriteFrameName(filename);

    rainDropSprite->setOpacity(RAIN_DROP_OPACITY);

    rainDropSprite->setScale(scale);

    rainDropSprite->setPosition(Point(
                random(origin.x + (rainDropSprite->getBoundingBox().size.width / 2),
                        visibleSize.width + origin.x - (rainDropSprite->getBoundingBox().size.width / 2)),
                random(origin.y,
                        visibleSize.height + origin.y)));
    layer->addChild(rainDropSprite);
}

void RainDrop::moveDown(float dt) {
    if(isOnScreen()) {
        auto speedCoef = (rainDropSprite->getScale() - MIN_RAIN_DROP_SCALE + (MAX_RAIN_DROP_SCALE - rainDropSprite->getScale()) * RAIN_SPEED_SCALE_DEP) /
                (MAX_RAIN_DROP_SCALE - MIN_RAIN_DROP_SCALE); //min value is 1/2 and max value is 1, direct proportional to scale

        rainDropSprite->setPositionY(rainDropSprite->getPositionY() -
                                     (RAIN_SPEED * speedCoef * visibleSize.height * dt));

    } else {
        resetRainDrop();
    }
}

bool RainDrop::isOnScreen() {
    return (rainDropSprite->getPositionY() + (rainDropSprite->getBoundingBox().size.height / 2)) > origin.y;
}

void RainDrop::resetRainDrop() {
//    rainDropSprite->setScale(random(MIN_RAIN_DROP_SCALE, MAX_RAIN_DROP_SCALE));

    rainDropSprite->setPosition(Point(
                random(
                    origin.x + (rainDropSprite->getBoundingBox().size.width / 2), 
                    visibleSize.width + origin.x - (rainDropSprite->getBoundingBox().size.width / 2)),
                visibleSize.height + origin.y + (rainDropSprite->getBoundingBox().size.height / 2)));
}
