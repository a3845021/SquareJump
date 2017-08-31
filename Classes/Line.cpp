#include "Line.h"
#include "Definitions.h"

USING_NS_CC;

Line::Line(Layer *layer)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto lineSprite = Sprite::createWithSpriteFrameName("line.png");
    lineSprite->setPosition(Point(
                visibleSize.width / 2 + origin.x,
                visibleSize.height / 2 + origin.y));

    layer->addChild(lineSprite);
    
    shiningSprite = Sprite::createWithSpriteFrameName("shiningLines.png");
    const float DISPLACEMENT_COEF = 0.15;
    shiningSprite->setPosition(Point(
                (visibleSize.width / 2) + origin.x - 
                (lineSprite->getContentSize().width * DISPLACEMENT_COEF),
                visibleSize.height / 2 + origin.y));

    layer->addChild(shiningSprite);
}
    
void Line::moveDown(float dt)
{
    if((shiningSprite->getPositionY() + (shiningSprite->getContentSize().height / 2)) > origin.y)
    {
        shiningSprite->setPositionY(shiningSprite->getPositionY() - 
                (GAME_SPEED * visibleSize.height * dt));
    }
    else
    {
        shiningSprite->setPositionY(visibleSize.height + origin.y + 
                (shiningSprite->getContentSize().height / 2));
    }
}
