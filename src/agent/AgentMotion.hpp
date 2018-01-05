//
//  AgentMotion.hpp
//  yaritori
//
//  Created by Hana on 2017/12/23.
//
//

#ifndef AgentMotion_hpp
#define AgentMotion_hpp

#include "ofMain.h"
#include "ScreenManager.hpp"
//#include "ofxGismo.h"
#include "ag_shape.h"

float frand() {
    return ofRandom(1.0);
}

int irand() {
    return int(ofRandom(0, 100.0));
}


struct vec2 {
    float x;
    float y;
};

class AgentMotion {
public:
    //Methods
    AgentMotion();
    void resetShape();
    void initModulation();
    void initVbo();
    
    void draw();
    void update();
    void updatePhase();
    void updatePosition();
    void updateColors();
    float getPointSize();
    float getLineWidth();
    
    //event
    void invertColor();
    
    //Variables
    ag_shape_t shape;
    ag_shape_t* pShape;
    int screenWidth, screenHeight;
    bool isActive;
    float size;
    float width_rate;
    float mov;
    vec2 center;
    float centerX ,centerY;

private:
    //VBO
    ofVbo nodeVbo, edgeVbo;
    ofVec2f nodePos[NODE_MAX];
    ofFloatColor nodeColors[NODE_MAX];
    ofIndexType edgeIndices[EDGE_MAX * 2];
    ofFloatColor edgeColors[EDGE_MAX * 2];
    
    ofShader shader;
    
    //Variables
    float color;
    
    //Modulation
    float velocityX[NODE_MAX];
    float velocityY[NODE_MAX];
    float modStep[NODE_MAX];
    float carStep[NODE_MAX];
    float grayScale;
    const float dt = 0.04f;
    float t;
};




//////////////////////////// PREVIOUS ////////////////////////////////
//
////Static Values
//constexpr int CONNECTION_MAX = 5;
//constexpr int NODES_MAX = 20;
//constexpr int LINE_VERTICES_MAX = NODES_MAX * CONNECTION_MAX * 2;
//
////Each node
//struct Node {
//    int id;
//    float x, y, size;
//    float velocityX, velocityY;
//    float modStep, carStep;
//    float modPhase, carPhase;
//    
//    int connectionNum;
//    int connectedTo[CONNECTION_MAX];
//};
//
////Node container
//struct Nodes {
//    float scale_x;  //Center
//    float scale_y;
//    float size;
//    Node node[NODES_MAX];
//    int nodeNum;
//    float mov;
//};
//
//
//class AgentMotion {
//public:
//    //Methods
//    AgentMotion();
//    void initModulation(int index);
//    void initNodes();
//    void initNode(int index);
//    void initVbo();
//    
//    void draw();
//    void update();
//    void updatePhase(int index);
//    void updatePosition(int index);
//    void updateColors();
//    float getPointSize();
//    float getLineWidth();
//    
//    //event
//    void invertColor();
//    
//    //Variables
//    Nodes nodes;
//    int screenWidth, screenHeight;
//    bool isActive;
//    float* width_rate;
//    
//private:
//    //VBO
//    ofVbo nodeVbo, lineVbo;
//    ofVec2f nodePos[NODES_MAX];
//    ofFloatColor nodeColors[NODES_MAX * CONNECTION_MAX];
//    ofIndexType lineIndex[LINE_VERTICES_MAX];
//    ofFloatColor lineColors[LINE_VERTICES_MAX];
//    
//    
//    //Variables
//    int lineNum;
//    float phase, nodeX, nodeY;
//    float grayScale;
//
//};
// 
//

#endif /* AgentMotion_hpp */
