#ifndef __LINE_H__
#define __LINE_H__

#include "cocos2d.h"

class Line {
public:
    explicit Line(cocos2d::Scene *scene, const std::string &fileName);
    void moveDown(float dt);
    cocos2d::Sprite *getLineSprite() const;
    void setPositionX(const float &position);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite *lineSprite;
    std::deque<cocos2d::Sprite *> lineNoiseSpriteDeque;
};
#endif // __LINE_H__
