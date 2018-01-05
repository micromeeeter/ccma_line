//
//  ScreenManager.hpp
//  viewPortTest
//
//  Created by Hana on 2017/12/25.
//
//

#ifndef ScreenManager_hpp
#define ScreenManager_hpp

#include "ofMain.h"

//Variables for screen position
constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;  //This is 1.0

//Length : real length (mm)
constexpr int SCREEN_LENGTH_W = 4000;
constexpr int SCREEN_LENGTH_H = 4000;
constexpr int CANVAS_LENGTH_W = 4200 * 4;
constexpr int CANVAS_LENGTH_H = 4200;
constexpr int MARGIN_LENGTH = (CANVAS_LENGTH_H - SCREEN_LENGTH_H) * 0.5;

constexpr float PxPerMm = WINDOW_HEIGHT / SCREEN_LENGTH_H;
constexpr float screen_margin =  MARGIN_LENGTH * WINDOW_HEIGHT / SCREEN_LENGTH_H;

constexpr float CANVAS_WIDTH = WINDOW_HEIGHT * 3 + screen_margin * 4;
constexpr float CANVAS_HEIGHT = WINDOW_HEIGHT +  screen_margin * 2;
constexpr int SCREEN_CENTER = WINDOW_HEIGHT * 0.5;

//for black box
constexpr int DISPLAY_MARGIN_X = WINDOW_HEIGHT;
constexpr int DISPLAY_MARGIN_W = WINDOW_WIDTH - WINDOW_HEIGHT;


enum screen_pos_e {
    SCREEN_POS_LEFT,
    SCREEN_POS_CENTER,
    SCREEN_POS_RIGHT,
};

static ofVec2f leftScreen = ofVec2f(-screen_margin, screen_margin);
static ofVec2f centerScreen = ofVec2f(-(WINDOW_HEIGHT + screen_margin * 2), screen_margin);
static ofVec2f rightScreen = ofVec2f(-(WINDOW_HEIGHT*2 + screen_margin * 3), screen_margin);

static ofVec2f targetScreen = leftScreen;

void invertBackground();
void setScreenPos(screen_pos_e screenPos);
void screenBegin();
void screenEnd();




#endif /* ScreenManager_hpp */
