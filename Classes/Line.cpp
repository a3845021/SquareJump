#include "Line.h"

USING_NS_CC;

Line::Line(Layer *layer)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto lineSprite = Sprite::create("line.png");
    lineSprite->setPosition(Point(
                visibleSize.width / 2 + origin.x,
                visibleSize.height / 2 + origin.y));

    layer->addChild(lineSprite);
    
    shiningSprite = Sprite::create("whiteLines.png");
    shiningSprite->setPosition(Point(
                visibleSize.width / 2 + origin.x,
                visibleSize.height / 2 + origin.y));

    layer->addChild(shiningSprite);
}
