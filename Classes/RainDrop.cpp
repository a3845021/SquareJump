#include "RainDrop.h"
#include "Definitions.h"

USING_NS_CC;

RainDrop::RainDrop(Layer *layer, const std::string& filename)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
   
    rainDropSprite = Sprite::createWithSpriteFrameName(filename);

    rainDropSprite->setOpacity(RAIN_DROP_OPACITY);

    auto randomScale = random(MIN_RAIN_DROP_SCALE, MAX_RAIN_DROP_SCALE);
    rainDropSprite->setScale(randomScale);

    speedCoef = (randomScale - MIN_RAIN_DROP_SCALE + (MAX_RAIN_DROP_SCALE - randomScale) * RAIN_SCALE_SPEED_COEFFICIENT) /
                (MAX_RAIN_DROP_SCALE - MIN_RAIN_DROP_SCALE);

    rainDropSprite->setPosition(Point(
                random(origin.x + (rainDropSprite->getBoundingBox().size.width / 2),
                        visibleSize.width + origin.x - (rainDropSprite->getBoundingBox().size.width / 2)),
                random(origin.y,
                        visibleSize.height + origin.y)));
    layer->addChild(rainDropSprite);
}

void RainDrop::moveDown(float dt)
{
    if((rainDropSprite->getPositionY() + (rainDropSprite->getBoundingBox().size.height / 2)) > origin.y)
    {
        fall(dt);
    }
    else
    {
        resetRainDrop();
    }
}

void RainDrop::fall(float dt)
{
    rainDropSprite->setPositionY(rainDropSprite->getPositionY() - 
            (RAIN_SPEED * speedCoef * visibleSize.height * dt));
}

void RainDrop::resetRainDrop()
{
    auto randomScale = random(MIN_RAIN_DROP_SCALE, MAX_RAIN_DROP_SCALE);
    rainDropSprite->setScale(randomScale);
    
    speedCoef = (randomScale - MIN_RAIN_DROP_SCALE + (MAX_RAIN_DROP_SCALE - randomScale) * RAIN_SCALE_SPEED_COEFFICIENT) /
                (MAX_RAIN_DROP_SCALE - MIN_RAIN_DROP_SCALE);

    rainDropSprite->setPosition(Point(
                random<int>(
                    origin.x + (rainDropSprite->getBoundingBox().size.width / 2), 
                    visibleSize.width + origin.x - (rainDropSprite->getBoundingBox().size.width / 2)),
//                random<int>(
//                    visibleSize.height + origin.y + (rainDropSprite->getBoundingBox().size.height / 2),
//                    3 * visibleSize.height + origin.y)
                visibleSize.height + origin.y + (rainDropSprite->getBoundingBox().size.height / 2)
                ));
}
