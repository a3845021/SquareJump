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
    nextTriangleSideDistanceMap.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(Triangle::ScreenSide::LEFT),
                                       std::forward_as_tuple((Triangle::Side)random(0, 1), TRIANGLE_SPEED * visibleSize.height)); //TRIANGLE_SPEED * visibleSize.height will give 1 sec
    nextTriangleSideDistanceMap.emplace(std::piecewise_construct,
                                        std::forward_as_tuple(Triangle::ScreenSide::RIGHT),
                                        std::forward_as_tuple((Triangle::Side)random(0, 1), TRIANGLE_SPEED * visibleSize.height));


}

void TriangleManager::createAndMoveTriangles(float dt) {
    for(auto & [screenSide, trianglesDeque]: trianglesMap) {
        for(auto &triangle: trianglesDeque) {
            triangle.moveDown(dt);
        }
    }

    for(auto & [screenSide, trianglesDeque]: trianglesMap) {
        if(!trianglesDeque.empty()) {
            if(!trianglesDeque.front().inUse()) {
                trianglesDeque.pop_front();
            }
        }
    }

    //decrement distance till next Triangle
    for(auto & [screenSide, sideDistancePair]: nextTriangleSideDistanceMap) {
        sideDistancePair.second -= TRIANGLE_SPEED * visibleSize.height * dt;
    }

    //add triangle when needed and set side and distance till next
    for(auto & [screenSide, trianglesDeque]: trianglesMap) {
        if(shouldCreateTriangle(screenSide)) {
            trianglesDeque.emplace_back(layer, screenSide, nextTriangleSideDistanceMap.at(screenSide).first);
            updateNextTriangleSideDistanceMap(screenSide);
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
        float minDistance = (MIN_TRIANGLES_TILL_NEXT_SAME_SIDE + 1) * lastTriangleHeight;
        float maxDistance = (MAX_TRIANGLES_TILL_NEXT_SAME_SIDE + 1) * minDistance;
        nextTriangleSideDistanceMap.at(screenSide).second = random(minDistance, maxDistance);
    }else { //next triangle's side is different then last triangle's side
        float minDistance = (MIN_TRIANGLES_TILL_NEXT_DIFF_SIDE + 1) * lastTriangleHeight;
        float maxDistance = (MAX_TRIANGLES_TILL_NEXT_DIFF_SIDE + 1) * minDistance;
        nextTriangleSideDistanceMap.at(screenSide).second = random(minDistance, maxDistance);
    }
    nextTriangleSideDistanceMap.at(screenSide).first = newSide;
}
