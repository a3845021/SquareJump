#include <cmath>
#include <utility>
#include "Rain.h"
#include "Definitions.h"

USING_NS_CC;

Rain::Rain(Scene *scene) {

    auto rainDropScaleRangeMap = getScaleRangeMap();
    auto rainNode = Node::create();

    auto winSize = Director::getInstance()->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    rainNode->setPosition(winSize.width/2, winSize.height/2);

    auto visibleSizeDiagonal = std::sqrt(std::pow(visibleSize.height, 2.0f) + std::pow(visibleSize.width, 2.0f));

    rainNode->setContentSize(Size(visibleSizeDiagonal, visibleSizeDiagonal));

    rainNode->setAnchorPoint(Vec2(0.5f, 0.5f));
    rainNode->setRotation(-RAIN_ANGLE);

    for(auto elem: rainDropScaleRangeMap) {
        for(int i = 0; i < elem.second; ++i) {
            rainDrops.emplace_back(RainDrop(rainNode, "rain2.png", elem.first));
        }
    }

    scene->addChild(rainNode);
}

void Rain::moveDown(float dt) {
    for(auto &rainDrop: rainDrops)
        rainDrop.moveDown(dt);
}

std::map<std::pair<float, float>, int> Rain::getScaleRangeMap() {
    std::default_random_engine generator;
    std::normal_distribution<float> normal_distribution = std::normal_distribution<float>(0.0f, RAIN_DROP_SCALE_STANDARD_DEVIATION);

    const int nrolls = 10000;
    std::vector<int> p1(RAIN_DROP_SCALE_RANGES);

    // generate normal distributed array
    for(int i = 0; i < nrolls; ++i) {
        float number = normal_distribution(generator);
        if ((number>=0)&&(number<RAIN_DROP_SCALE_RANGES)) ++p1[int(number)];
    }

    std::discrete_distribution<int> discrete_distribution(p1.begin(), p1.end());

    // generate discrete distributed array based on normal distributed array calculated previously
    // sum of elements of this array will be equal to the number of rolls
    std::vector<int> p2(RAIN_DROP_SCALE_RANGES);
    for(int i = 0; i < nrolls; ++i) {
        ++p2[discrete_distribution(generator)];
    }

    for(auto &value : p2) {
        value = value * RAIN_DROPS_NUMBER / nrolls;
    }

    auto scaleStep = (MAX_RAIN_DROP_SCALE - MIN_RAIN_DROP_SCALE) / RAIN_DROP_SCALE_RANGES;

    std::map<std::pair<float, float>, int> rainDropScaleRangeMap = {};

    for(int i = 0; i < RAIN_DROP_SCALE_RANGES; ++i) {
        auto minScale = MIN_RAIN_DROP_SCALE + i * scaleStep;
        auto maxScale = MIN_RAIN_DROP_SCALE + (i+1) * scaleStep;
        std::pair<float, float> rangeScale(minScale, maxScale);
        rainDropScaleRangeMap[rangeScale] = p2[i];
    }

    return rainDropScaleRangeMap;
}
