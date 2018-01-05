//
//  LineDrawer.hpp
//  ccma_line
//
//  Created by Momoha Matsuhashi on 2018/01/05.
//
//

#ifndef LineDrawer_hpp
#define LineDrawer_hpp

const int CANVAS_WIDTH = 800;
const int CANVAS_HEIGHT = 800;

#include "ofMain.h"

class LineDrawer{
public:
    LineDrawer();
    
    void lineTo(float x, float y);
    
    float myPos_x, myPos_y;
    
private:
    void updateVertsPos(float target_x, float target_y);
    
    float theta;
    
    static constexpr float maxR = 0.07;
    
    static const int NUM = 30;  //num of feature points
    ofVec2f verts[NUM + 2]; // + myPos + targetPos
    ofVbo vbo;
};



#endif /* LineDrawer_hpp */
