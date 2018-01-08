//
//  LineDrawer.hpp
//  ccma_line
//
//  Created by Momoha Matsuhashi on 2018/01/05.
//
//

#ifndef LineDrawer_hpp
#define LineDrawer_hpp

#include "ScreenManager.hpp"
#include "ofMain.h"
#include "timed_interpolation.hpp"

class LineDrawer{
public:
    LineDrawer();
    
    void lineTo(float x, float y);
    
    float myPos_x, myPos_y;
    
private:
    void updateVertsPos(float target_x, float target_y);
    
    static constexpr float cycle = 1. * 1000.;   //msec
    float currentPhase, theta;
    static constexpr float maxR = 0.015;
    
    static const int NUM = 30;  //num of feature points
    ofVec2f verts[NUM + 2]; // + myPos + targetPos
    ofVbo vbo;
    
    TimedInterpolation interpolation;
};



#endif /* LineDrawer_hpp */
