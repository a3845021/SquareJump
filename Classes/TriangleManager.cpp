#include "TriangleManager.h"
#include "Definitions.h"

USING_NS_CC;

TriangleManager::TriangleManager(cocos2d::Layer *layer): layer(layer) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    trianglesMap.emplace(std::piecewise_construct,
                         std::forward_as_tuple(Triangle::ScreenSide::LEFT), std::forward_as_tuple());
    trianglesMap.emplace(std::piecewise_construct,
                         std::forward_as_tuple(Triangle::ScreenSide::RIGHT), std::forward_as_tuple());
    float oneSecondDistance = TRIANGLE_SPEED * visibleSize.height;
    nextTriangleSideDistanceMap.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(Triangle::ScreenSide::LEFT),
                                       std::forward_as_tuple((Triangle::Side)random(0, 1),
                                                             random(MIN_SECOND_TILL_INIT_TRIANGLE * oneSecondDistance,
                                                                    MAX_SECOND_TILL_INIT_TRIANGLE * oneSecondDistance))); //TRIANGLE_SPEED * visibleSize.height will give 1 sec
    nextTriangleSideDistanceMap.emplace(std::piecewise_construct,
                                        std::forward_as_tuple(Triangle::ScreenSide::RIGHT),
                                        std::forward_as_tuple((Triangle::Side)random(0, 1),
                                                              random(MIN_SECOND_TILL_INIT_TRIANGLE * oneSecondDistance,
                                                                     MAX_SECOND_TILL_INIT_TRIANGLE * oneSecondDistance)));


}

void TriangleManager::createAndMoveTriangles(float dt) {
    for(auto &elem : trianglesMap) {
        for(auto &triangle: elem.second) {
            triangle.moveDown(dt);
        }
    }

    for(auto &elem: trianglesMap) {
        if(!elem.second.empty()) {
            if(!elem.second.front().inUse()) {
                elem.second.pop_front();
            }
        }
    }

    //decrement distance till next Triangle
    for(auto &elem: nextTriangleSideDistanceMap) {
        elem.second.second -= TRIANGLE_SPEED * visibleSize.height * dt;
    }

    //add triangle when needed and set side and distance till next
    for(auto &elem: trianglesMap) {
        if(shouldCreateTriangle(elem.first)) {
            elem.second.emplace_back(layer, elem.first, nextTriangleSideDistanceMap.at(elem.first).first);
            updateNextTriangleSideDistanceMap(elem.first);
        }
    }
}

bool TriangleManager::shouldCreateTriangle(const Triangle::ScreenSide &screenSide) const {
    return nextTriangleSideDistanceMap.at(screenSide).second < 0;
}

void TriangleManager::updateNextTriangleSideDistanceMap(const Triangle::ScreenSide &screenSide) {
    auto newSide = (Triangle::Side)random(0, 1); //0 or 1, LEFT or RIGHT
    auto lastTriangleHeight = trianglesMap.at(screenSide).back().getSprite()->getContentSize().height;
    if(newSide == nextTriangleSideDistanceMap.at(screenSide).first) {//next triangle's side is same as last triangle's side
        float minDistance = MIN_TRIANGLES_TILL_NEXT_SAME_SIDE * lastTriangleHeight;
        float maxDistance = MAX_TRIANGLES_TILL_NEXT_SAME_SIDE * lastTriangleHeight;
        nextTriangleSideDistanceMap.at(screenSide).second = random(minDistance, maxDistance);
    }else { //next triangle's side is different then last triangle's side
        float minDistance = TRIANGLE_SPEED * visibleSize.height * MOVING_ANIMATION_TIME + //distance representing visual ilusion of vertical movement
                                                                                          //that happen when square jumps to other side
                            MIN_TRIANGLES_TILL_NEXT_DIFF_SIDE * lastTriangleHeight;       //plus specific desired coeficient, to simplify game.
        float maxDistance = MAX_TRIANGLES_TILL_NEXT_DIFF_SIDE * lastTriangleHeight;
        nextTriangleSideDistanceMap.at(screenSide).second = random(minDistance, maxDistance);
    }
    nextTriangleSideDistanceMap.at(screenSide).first = newSide;
}
