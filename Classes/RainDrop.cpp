#include "RainDrop.h"
#include "Definitions.h"

USING_NS_CC;

RainDrop::RainDrop(Layer *layer, const std::string& fileName)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
   
    rainDropSprite = Sprite::create(fileName);

    rainDropSprite->setScale(4);

    auto initialRandomPosition = Point(
                random<int>(origin.x + (rainDropSprite->getBoundingBox().size.width / 2), 
                    visibleSize.width + origin.x - (rainDropSprite->getBoundingBox().size.width / 2)),
                visibleSize.height + origin.y + (rainDropSprite->getBoundingBox().size.height / 2));
    rainDropSprite->setPosition(initialRandomPosition);
    
    layer->addChild(rainDropSprite);
}

void RainDrop::moveDown(float dt)
{
    if((rainDropSprite->getPositionY() + (rainDropSprite->getBoundingBox().size.height / 2)) > origin.y)
    {
        rainDropSprite->setPositionY(rainDropSprite->getPositionY() - 
                (MOVE_SPEED * visibleSize.height * dt));
    }
    else
    {
        rainDropSprite->setPositionY(visibleSize.height + origin.y + 
                (rainDropSprite->getBoundingBox().size.height / 2));
    }
}
