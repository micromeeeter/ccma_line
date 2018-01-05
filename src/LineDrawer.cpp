//
//  LineDrawer.cpp
//  ccma_line
//
//  Created by Momoha Matsuhashi on 2018/01/05.
//
//

#include "LineDrawer.hpp"

LineDrawer::LineDrawer(){
    myPos_x = 0.5;
    myPos_y = 0.5;
    
    for(int i = 0; i < NUM + 2; i++){
        verts[i].set(0.5 * CANVAS_WIDTH, 0.5 * CANVAS_HEIGHT);
    }
    
    vbo.setVertexData(verts, NUM + 2, GL_DYNAMIC_DRAW);
}

void LineDrawer::updateVertsPos(float target_x, float target_y){
    theta = atan2(target_y - myPos_y, target_x - myPos_x);
    
    verts[0].set(myPos_x * CANVAS_WIDTH, myPos_y * CANVAS_HEIGHT);
    for(int i = 1; i <= NUM; i++){
        float r = maxR / NUM * (NUM + 1 - i);
        float th = theta + PI * 0.5 + PI * i;
        float x = myPos_x + (target_x - myPos_x) / (NUM + 1) * i + r * cos(th);
        float y = myPos_y + (target_y - myPos_y) / (NUM + 1) * i + r * sin(th);
        verts[i].set(x * CANVAS_WIDTH, y * CANVAS_HEIGHT);
    }
    verts[NUM + 1].set(target_x * CANVAS_WIDTH, target_y * CANVAS_HEIGHT);
}

void LineDrawer::lineTo(float x, float y){
    updateVertsPos(x, y);
    
    glLineWidth(1.);
    glColor3f(0., 0., 0.);
    vbo.updateVertexData(verts, NUM + 2);
    vbo.draw(GL_LINE_STRIP, 0, NUM + 2);
}
