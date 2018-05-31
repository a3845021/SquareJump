#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

//triangle
const float GAME_SPEED_COEF = 0.25f;
const float MIN_SECOND_TILL_INIT_TRIANGLE = 1.0f;
const float MAX_SECOND_TILL_INIT_TRIANGLE = 3.0f;
const int MIN_TRIANGLES_TILL_NEXT_SAME_SIDE = 1;
const int MAX_TRIANGLES_TILL_NEXT_SAME_SIDE = MIN_TRIANGLES_TILL_NEXT_SAME_SIDE + 8;
const int MIN_TRIANGLES_TILL_NEXT_DIFF_SIDE = 1;
const int MAX_TRIANGLES_TILL_NEXT_DIFF_SIDE = MIN_TRIANGLES_TILL_NEXT_DIFF_SIDE + 8;
const int TRIANGLE_COLLISION_BITMASK = 0x00000001;

//rain
const int RAIN_DROP_SCALE_RANGES = 3;
const float RAIN_SPEED = 0.9f;
const float RAIN_SPEED_SCALE_COEF = 0.35f; //0->1, 0 means rainDrop with smaller scale move slower, 1 means rainDrops have same speed
const int RAIN_DROPS_NUMBER = 150;
const float RAIN_DROP_SCALE_STANDARD_DEVIATION = 5.0f;
const float MIN_RAIN_DROP_SCALE = 0.5f;
const float MAX_RAIN_DROP_SCALE = 2.8f;
const GLubyte RAIN_DROP_OPACITY = 140; //(0 -> 255) unsigned char
const float RAIN_ANGLE = 15.0f;

//square
const int ROTATION_NUMBER = 1;
const float SQUARE_ANIMATION_TIME = 0.5f;
const int SQUARE_COLLISION_BITMASK = 0x00000002;

//score
const float SCORE_FONT_SIZE = 99.35f;
const std::string MAIN_FONT = "fonts/AldotheApache.ttf";
const int MAIN_FONT_COLOR_RED = 19;
const int MAIN_FONT_COLOR_GREEN= 43;
const int MAIN_FONT_COLOR_BLUE = 91;
const int SCORING_LINE_COLLISION_BITMASK = 0x00000003;
const float SCORE_POSITION_X_COEF = 0.75f;
const float SCORE_POSITION_Y_COEF = 0.85f;
#endif// __DEFINITIONS_H__
