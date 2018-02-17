#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

//line
const float SHINING_LINES_SPEED = 0.45f;

//rain
const int RAIN_DROP_SCALE_RANGES = 9;
const float RAIN_SPEED = 0.9f;
const float RAIN_SPEED_SCALE_COEF = 0.5f; //0->1, 0 means rainDrop with smaller scale move slower, 1 means rainDrops have same speed
const int RAIN_DROPS_NUMBER = 200;
const float RAIN_DROP_SCALE_STANDARD_DEVIATION = 5.0f;
const float MIN_RAIN_DROP_SCALE = 0.5f;
const float MAX_RAIN_DROP_SCALE = 2.0f;
const GLubyte RAIN_DROP_OPACITY = 140; //(0 -> 255) unsigned char

//square
const int ROTATION_NUMBER = 1;
const float MOVING_ANIMATION_TIME = 0.4f;
const float ROTATE_ANIMATION_TIME = 0.4f; // seconds

#endif// __DEFINITIONS_H__
