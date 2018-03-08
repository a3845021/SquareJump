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
                                       std::forward_as_tuple((Triangle::Side)random(0, 1), TRIANGLE_SPEED * visibleSize.height));
    nextTriangleSideDistanceMap.emplace(std::piecewise_construct,
                                        std::forward_as_tuple(Triangle::ScreenSide::RIGHT),
                                        std::forward_as_tuple((Triangle::Side)random(0, 1), TRIANGLE_SPEED * visibleSize.height));


}

void TriangleManager::createAndMoveTriangles(float dt) {
    for (auto & [screenSide, trianglesDeque]: trianglesMap) {
        for (auto &triangle: trianglesDeque) {
            triangle.moveDown(dt);
        }
    }

    for (auto & [screenSide, trianglesDeque]: trianglesMap) {
        if (!trianglesDeque.empty()) {
            if (!trianglesDeque.front().inUse()) {
                trianglesDeque.pop_front();
            }
        }
    }

    //decrement distance till next Triangle
    for (auto & [screenSide, sideDistancePair]: nextTriangleSideDistanceMap) {
        sideDistancePair.second -= TRIANGLE_SPEED * visibleSize.height * dt;
    }

    for (auto & [screenSide, trianglesDeque]: trianglesMap) {
        if (shouldCreateTriangle(screenSide)) {
            trianglesDeque.emplace_back(layer, screenSide, nextTriangleSideDistanceMap.at(screenSide).first);
            updateNextTriangleSideDistanceMap(screenSide);
        }
    }
}

bool TriangleManager::shouldCreateTriangle(const Triangle::ScreenSide &screenSide) {
    return nextTriangleSideDistanceMap.at(screenSide).second < 0;
}

void TriangleManager::createTriangle(const Triangle::ScreenSide &screenSide) {
    trianglesMap.at(screenSide).emplace_back(layer, screenSide, nextTriangleSideDistanceMap.at(screenSide).first);
}

void TriangleManager::updateNextTriangleSideDistanceMap(const Triangle::ScreenSide &screenSide) {
    nextTriangleSideDistanceMap.at(screenSide).first = (Triangle::Side)random(0, 1);
    nextTriangleSideDistanceMap.at(screenSide).second = trianglesMap.at(screenSide).back().getSprite()->getContentSize().height; //TRIANGLE_SPEED * visibleSize.height;
}
