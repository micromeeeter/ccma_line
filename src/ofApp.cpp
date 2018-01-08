#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(CANVAS_WIDTH, CANVAS_HEIGHT);
    
    gui.setup();
    gui.add(target_x.setup("target_x", 0.75, 0., 1.));
    gui.add(target_y.setup("target_y", 0.5, 0., 1.));
    
    agent1.center.x = 0.25;
    agent2.center.x = 0.75;

}

//--------------------------------------------------------------
void ofApp::update(){
    agent1.update();
    agent2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    screenBegin();
    
    agent1.draw();
    agent2.draw();
    
    line.lineTo(target_x, target_y);

    

    
    screenEnd();
    
    
    //gui.draw();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
