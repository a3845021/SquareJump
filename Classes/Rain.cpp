#include <iostream>
#include "Rain.h"
#include "Definitions.h"

USING_NS_CC;

Rain::Rain(Layer *layer) {

    auto rainDropDiscreteDistrebutedScaleAmoutMap = getDiscreteDistributedScaleAmountMap();

    for(auto elem: rainDropDiscreteDistrebutedScaleAmoutMap) {
        std::cout << elem.first << ": " << elem.second << std::endl;
        for(int i = 0; i < elem.second; ++i) {
            rainDrops.emplace_back(RainDrop(layer, "rainDrop.png", elem.first));
        }
    }
}

void Rain::moveDown(float dt) {
    for(auto &rainDrop: rainDrops)
        rainDrop.moveDown(dt);
}

std::map<float, int> Rain::getDiscreteDistributedScaleAmountMap() {
    std::default_random_engine generator;
    std::normal_distribution<float> normal_distribution = std::normal_distribution<float>(0.0f, RAIN_DROP_SCALE_STANDARD_DEVIATION);

    const int nrolls = 10000;
    std::vector<int> p1(RAIN_DROP_SCALES_NUM);

    // generate normal distributed array
    //
    for(int i = 0; i < nrolls; ++i) {
        float number = normal_distribution(generator);
        if ((number>=0)&&(number<RAIN_DROP_SCALES_NUM)) ++p1[int(number)];
    }

//    for(int i = 0; i < p1.size(); ++i) {
//        std::cout << p1[i] << std::endl;
//    }

    std::discrete_distribution<int> discrete_distribution(p1.begin(), p1.end());

    // generate discrete distributed array based on normal distributed array calculated previously
    // sum of elements of this array will be equal to the number of rolls
    std::vector<int> p2(RAIN_DROP_SCALES_NUM);
    for(int i = 0; i < nrolls; ++i) {
        ++p2[discrete_distribution(generator)];
    }

    for(auto &value : p2) {
        value = value * RAIN_DROPS_NUMBER / nrolls;
    }

//    for(int i = 0; i < p2.size(); ++i) {
//        std::cout << p2[i] << std::endl;
//    }

    auto scaleStep = (MAX_RAIN_DROP_SCALE - MIN_RAIN_DROP_SCALE) / (RAIN_DROP_SCALES_NUM - 1);

    std::map<float, int> rainDropScaleAmountMap;

    for(int i = 0; i < RAIN_DROP_SCALES_NUM; ++i) {
        auto scale = MIN_RAIN_DROP_SCALE + i * scaleStep;
        rainDropScaleAmountMap[scale] = p2[i];
    }

    return rainDropScaleAmountMap;
}
