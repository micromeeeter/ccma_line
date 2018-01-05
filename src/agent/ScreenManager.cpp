//
//  ScreemManager.cpp
//  viewPortTest
//
//  Created by Hana on 2017/12/25.
//
//

#include "ScreenManager.hpp"

bool drawWhiteBack = true;

void setScreenPos(screen_pos_e screenPos) {
    switch (screenPos) {
        case SCREEN_POS_LEFT:
            targetScreen = leftScreen;
            break;
        case SCREEN_POS_CENTER:
            targetScreen = centerScreen;
            break;
        case SCREEN_POS_RIGHT:
            targetScreen = rightScreen;
            break;
        default:
            break;
    }
}

void screenBegin() {

    ofBackground(0);
    
    //Masking
    if(drawWhiteBack) {
        ofSetColor(255);
        ofDrawRectangle(0, 0, WINDOW_HEIGHT, WINDOW_HEIGHT);
    }
    
    ofPushMatrix();
    ofTranslate(targetScreen);
}


void screenEnd() {
    ofPopMatrix();
}

void invertBackground() {
    drawWhiteBack = !drawWhiteBack;
}
