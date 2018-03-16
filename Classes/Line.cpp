#include "Line.h"
#include "Definitions.h"

USING_NS_CC;

Line::Line(Layer *layer, const std::string &fileName) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    lineSprite = Sprite::createWithSpriteFrameName(fileName +".png");
    lineSprite->setName(fileName);
    lineSprite->setPositionY(visibleSize.height / 2 + origin.y);

    layer->addChild(lineSprite);

    auto lineSpriteNoise = Sprite::createWithSpriteFrameName(fileName + "Noise.png");
    lineSpriteNoise->setPosition(Point(
            lineSprite->getContentSize().width / 2,
            lineSprite->getContentSize().height / 2));
    lineNoiseSpriteDeque.emplace_back(lineSpriteNoise);
    lineSprite->addChild(lineSpriteNoise);

    lineSpriteNoise = Sprite::createWithSpriteFrameName(fileName + "Noise.png");
    lineSpriteNoise->setPosition(Point(
            lineSprite->getContentSize().width / 2,
            lineSprite->getContentSize().height / 2 + lineSpriteNoise->getContentSize().height));
    lineNoiseSpriteDeque.emplace_back(lineSpriteNoise);
    lineSprite->addChild(lineSpriteNoise);
}
    
void Line::moveDown(float dt) {
    for(auto & lineSpriteNoise: lineNoiseSpriteDeque) {
        lineSpriteNoise->setPositionY(lineSpriteNoise->getPositionY() - GAME_SPEED_COEF * visibleSize.height * dt);
    }

    //move front lineNoiseSprite to the back of deque and change it's position to be on top of last lineNoiseSprite
    if(lineNoiseSpriteDeque.front()->getPositionY() + lineNoiseSpriteDeque.front()->getContentSize().height / 2 < origin.y) {
        auto lineNoiseSprite = lineNoiseSpriteDeque.front();
        lineNoiseSpriteDeque.pop_front();
        lineNoiseSpriteDeque.emplace_back(lineNoiseSprite);
        lineNoiseSprite->setPositionY(lineNoiseSprite->getPositionY() + 2 * lineNoiseSprite->getContentSize().height);
    }
}

Sprite *Line::getLineSprite() const {
    return lineSprite;
}

void Line::setPositionX(const float &value) {
    lineSprite->setPositionX(value);
}


