#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

//line
const float DISPLACEMENT_COEF = 0.15f;
const float SHINING_LINES_SPEED = 0.45f;

//triangle
const float TRIANGLE_SPEED = 0.05f;
const float MIN_SECOND_TILL_INIT_TRIANGLE = 1.0f;
const float MAX_SECOND_TILL_INIT_TRIANGLE = 3.0f;
const int MIN_TRIANGLES_TILL_NEXT_SAME_SIDE = 1;
const int MAX_TRIANGLES_TILL_NEXT_SAME_SIDE = MIN_TRIANGLES_TILL_NEXT_SAME_SIDE + 8;
const int MIN_TRIANGLES_TILL_NEXT_DIFF_SIDE = 1;
const int MAX_TRIANGLES_TILL_NEXT_DIFF_SIDE = MIN_TRIANGLES_TILL_NEXT_DIFF_SIDE + 8;
const int TRIANGLE_COLLISION_BITMASK = 0x00000001;

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
const float MOVING_ANIMATION_TIME = 5.0f;
const float ROTATE_ANIMATION_TIME = 5.0f; // seconds
const int SQUARE_COLLISION_BITMASK = 0x00000002;

#endif// __DEFINITIONS_H__
