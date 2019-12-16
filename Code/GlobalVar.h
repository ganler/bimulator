#ifndef __CLOBAL__
#define __CLOBAL__
#include <opencv2/opencv.hpp>
#include "ray_tracing.h"
//#include "OpenGLDraw.h"

extern cv::Mat view_global;
extern ray_tracing_controller rtc;

extern float ball_positions[10][3];
extern float camera_eye[3];
extern float camera_look_at[3];
extern float ball_rotateAngle[10];
extern float ball_rotateVec[10][3];
extern bool ball_selected[10];
extern bool ball_die[10];

extern float shadow_factor[VIEW_ROW][VIEW_COL];
extern float sample_results[VIEW_ROW][VIEW_COL][3];
extern int nowHero;
#endif