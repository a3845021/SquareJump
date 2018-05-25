#ifndef __TRIANGLE_MANAGER_H__
#define __TRIANGLE_MANAGER_H__

#include "Triangle.h"

class TriangleManager {
public:
    explicit TriangleManager(cocos2d::Scene *scene);

    void createAndMoveTriangles(float dt);
    bool shouldCreateTriangle(const Triangle::ScreenSide &screenSide) const;

private:
    void updateNextTriangleSideDistanceMap(const Triangle::ScreenSide &screenSide);

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    std::map<Triangle::ScreenSide, std::deque<Triangle>> trianglesMap;
    std::map<Triangle::ScreenSide, std::pair<Triangle::Side, float>> nextTriangleSideDistanceMap;

    cocos2d::Scene *scene;
};


#endif //__TRIANGLE_MANAGER_H__
