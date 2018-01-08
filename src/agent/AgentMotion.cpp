//
//  AgentMotion.cpp
//  yaritori
//
//  Created by Hana on 2017/12/23.
//
//

#include "AgentMotion.hpp"


//Constant Values
constexpr float NODE_LENGTH_RANGE = 0.005;   //0.003
constexpr float NODE_LENGTH_MIN = 0.003;
constexpr float MOVE_SIZE = 0.1;
constexpr float M_2XPI = M_PI * 2.0;

constexpr float STEP_MAX = M_2XPI * 6.0f;
constexpr float STEP_MIN = M_2XPI * 4.0f;

//About length
constexpr float LINE_WIDTH = 0.5;
constexpr float NODE_SIZE = 4.0;
constexpr float TREMOR_RATIO = 0.125;
constexpr float STAY_RATIO = 1.0 - TREMOR_RATIO;



AgentMotion::AgentMotion() {
    color = 0.0;
    center.x = 0.5;
    center.y = 0.5;
    width_rate = 1.0f;
    mov = 0.01;
    size = 0.03;
    
    resetShape();
    initVbo();
    
//    shader.load("shader/shader.vert", "shader/shader.frag");

}

void AgentMotion::resetShape() {
    center.x = 0.5;
    center.y = 0.5;
    
    shape.node_count = int(NODE_MAX * frand());
    shape.edge_count = int(EDGE_MAX * frand());
    
    for(int i = 0; i < shape.node_count; i++) {
        shape.nodes[i].x = frand() - 0.5;
        shape.nodes[i].y = frand() - 0.5;
    }
    
    for (int i = 0; i <  shape.edge_count; i++) {
        shape.edges[i].node_id_a = (i % shape.node_count);
        shape.edges[i].node_id_b = (irand() % shape.node_count);
        while (shape.edges[i].node_id_a == shape.edges[i].node_id_b) {
            shape.edges[i].node_id_b =  irand() % shape.node_count;
        }
    }
    
    pShape = &this->shape;

}

void AgentMotion::initModulation() {
    ofVec2f vel = ofVec2f(frand() * 2.0 - 1.0, frand() * 2.0 - 1.0).getNormalized();
    
    for(int i = 0; i < NODE_MAX; i++) {
        velocityX[i] = vel.x;
        velocityY[i] = vel.y;
        
        modStep[i] = (STEP_MAX - STEP_MIN) * frand() + STEP_MIN;
        carStep[i] = (STEP_MAX - STEP_MIN) * frand() + STEP_MIN;
    }
    t = 0.0f;
}


void AgentMotion::initVbo() {
    for(int i = 0; i < pShape->node_count; i++) {
        ofVec2f pos;
        pos.x = ( center.x + (pShape->nodes[i].x * size)) * CANVAS_HEIGHT;
        pos.y = ( center.y + (pShape->nodes[i].y * size)) * CANVAS_HEIGHT;
        
        nodePos[i] = pos;
        nodeColors[i] = ofFloatColor(color);
    }
    
    for (int i = 0; i < pShape->edge_count * 2; i += 2) {
        int edge_index = i * 0.5;
        edgeIndices[i] = pShape->edges[edge_index].node_id_a;
        edgeIndices[i+1] = pShape->edges[edge_index].node_id_b;
        edgeColors[i] = ofFloatColor(color);
        edgeColors[i+1] = ofFloatColor(color);
    }
    
    nodeVbo.setVertexData(nodePos, pShape->node_count, GL_DYNAMIC_DRAW);
    nodeVbo.setColorData(nodeColors, pShape->node_count, GL_DYNAMIC_DRAW);
    
    edgeVbo.setVertexData(nodePos, pShape->node_count, GL_DYNAMIC_DRAW);
    edgeVbo.setColorData(edgeColors, pShape->edge_count, GL_DYNAMIC_DRAW);
    edgeVbo.setIndexData(edgeIndices, pShape->edge_count, GL_DYNAMIC_DRAW);
}

void AgentMotion::updateColors() {
    for(int i = 0; i < pShape->node_count; i++) {
        nodeColors[i] = ofFloatColor(color);
    }
    
    for (int i = 0; i < pShape->edge_count * 2; i += 2) {
        int edge_index = i * 0.5;
        edgeColors[i] = ofFloatColor(color);
        edgeColors[i+1] = ofFloatColor(color);
    }
    
    nodeVbo.updateColorData(nodeColors, pShape->node_count);
    edgeVbo.updateColorData(edgeColors, pShape->edge_count);
}

void AgentMotion::updatePosition() {
    for(int i = 0; i < pShape->node_count; i++) {
        ofVec2f pos;
        pos.x = ( center.x + (pShape->nodes[i].x * size)) * CANVAS_HEIGHT;
        pos.y = ( center.y + (pShape->nodes[i].y * size)) * CANVAS_HEIGHT;
        
        nodePos[i] = pos;
    }
    nodeVbo.updateVertexData(nodePos, pShape->node_count);
    edgeVbo.updateVertexData(nodePos, pShape->node_count);
}

void AgentMotion::update() {
    t += mov;
    
    if(M_2XPI < t) {
        t = 0.0f;
    }
    
//    t += 1.0;
//    if(30 < t) {
//        t = 0.0;
//    }
    
    this->updatePosition();
}

void AgentMotion::draw() {
    
//    shader.begin();
//    shader.setUniform1f("t", t);
//    shader.setUniform1f("color", color);
//    shader.setUniform1fv("carStep", carStep);
//    shader.setUniform1fv("modStep", modStep);
//    shader.setUniform1f("centerX", center.x*screenWidth);
//    shader.setUniform1f("centerY", center.y*screenWidth);
    
    
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPointSize(getPointSize());
    nodeVbo.draw(GL_POINTS, 0, pShape->node_count);
    
    
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(getLineWidth());
    edgeVbo.drawElements(GL_LINES, pShape->edge_count);
    
//    shader.end();
}



float AgentMotion::getPointSize() {
    float pointSize = 3.5;
    if(size < 0.02) {
        pointSize = 2.0;
    } else if (0.02 <= size && size < 0.03) {
        pointSize = 2.0;
    } else if(0.03 <= size && size < 0.04) {
        pointSize = 2.5;
    } else if(0.04 <= size && size < 0.05) {
        pointSize = 3.0;
    } else {
        pointSize += 8.0 * size;
    }
    
    return pointSize;
}

float AgentMotion::getLineWidth() {
    float lineWidth = 0.5;
    if(size <= 0.01) {
        lineWidth = 0.05;
    } else if (0.01 < size && size < 0.02) {
        lineWidth = 0.1;
    } else if(0.02 <= size && size < 0.05) {
        lineWidth = 0.25;
    }
    
    return lineWidth;
}

void AgentMotion::invertColor() {
    if (color == 1.0) {
        color = 0.0f;
    } else {
        color = 1.0;
    }
    
    this->updateColors();
}




////////////////////////// PREVIOUS ////////////////////////////////
//AgentMotion::AgentMotion() {
//    nodes.scale_x = 0.0;
//    nodes.scale_y = 0.0;
//    
//    //nodes.nodeNum = int(ofRandom(10, MAX_NODES));
//    nodes.nodeNum = NODES_MAX;
//    nodes.mov = 0.5;
//    //width_rate = 1.0;
//    
//    //Init Color
//    grayScale = 0.0;
//    
//    
//    //Init nodes
//    for(int i = 0; i < nodes.nodeNum; i++) {
//        initNode(i);    //  Set Node pos and connection
//        initModulation(i);  // Set Modulation
//    }
//    
//    
//    initVbo();  //VBO
//}
//
//void AgentMotion::initNode(int index) {
//    nodes.node[index].id = index;
//    
//    //Set Position
//    nodes.node[index].x = frand() - 0.5;    //Position of each node is currently random
//    nodes.node[index].y = frand() - 0.5;    //Prev :: -0.01, 0.01
//    
//    //Set Connection
//    if(nodes.nodeNum < 3) { //Connections are also random
//        nodes.node[index].connectionNum = int(ofRandom(1, 2));
//    } else {
//        nodes.node[index].connectionNum = int(ofRandom(1, CONNECTION_MAX));
//    }
//    
//    if(index < nodes.nodeNum -1 ) {
//        nodes.node[index].connectedTo[0] = (index + 1);
//    }
//    
//    for(int j = 1; j < nodes.node[index].connectionNum; j++) {
//        nodes.node[index].connectedTo[j] = int(ofRandom(nodes.nodeNum));
//    }
//}
//
//void AgentMotion::initNodes() {
//    for(int i = 0; i < nodes.nodeNum; i++) {
//        initNode(i);
//    }
//}
//
//void AgentMotion::initVbo() {
//    lineNum = 0;
//    int tmpWidth = ofGetWidth();
//    for(int i = 0; i < nodes.nodeNum; i++) {
//        int x = (nodes.node[i].x + nodes.scale_x) * tmpWidth;
//        int y = (nodes.node[i].y + nodes.scale_y) * tmpWidth;
//        //Node
//        nodePos[i] = ofVec2f(x, y);
//        nodeColors[i] = ofFloatColor(grayScale);
//        
//        //Line
//        for(int j = 0; j < nodes.node[i].connectionNum; j++) {
//            lineIndex[lineNum] = i; //This node
//            lineColors[lineNum] = ofFloatColor(grayScale);
//            lineNum++;
//            
//            lineIndex[lineNum] = nodes.node[i].connectedTo[j];  //Connected Node
//            lineColors[lineNum] = ofFloatColor(grayScale);
//            
//            lineNum++;
//        }
//    }
//    
//    nodeVbo.setVertexData(nodePos, nodes.nodeNum, GL_DYNAMIC_DRAW);
//    nodeVbo.setColorData(nodeColors, nodes.nodeNum, GL_DYNAMIC_DRAW);
//    
//    lineVbo.setVertexData(nodePos, nodes.nodeNum, GL_DYNAMIC_DRAW);
//    lineVbo.setIndexData(lineIndex, lineNum, GL_DYNAMIC_DRAW);
//    lineVbo.setColorData(lineColors, lineNum, GL_DYNAMIC_DRAW);
//}
//
//void AgentMotion::invertColor() {
//    if(grayScale == 1.0) {
//        grayScale = 0.0;
//    } else {
//        grayScale = 1.0;
//    }
//    
//    this->updateColors();
//}
//
//void AgentMotion::draw() {
//    glEnable(GL_POINT_SMOOTH);
//    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);
//    glPointSize(getPointSize());
//    nodeVbo.draw(GL_POINTS, 0, nodes.nodeNum);
//    
//    
//    glEnable(GL_LINE_SMOOTH);
//    glLineWidth(getLineWidth());
//    lineVbo.drawElements(GL_LINES, lineNum);
//}
//
///////////////////// UPDATE POSITION /////////////////////
//
//void AgentMotion::updatePhase(int index) {
//    // Update Phases
//    nodes.node[index].carPhase += nodes.node[index].carStep * nodes.mov;    //Carrier
//    if(M_2XPI < nodes.node[index].carPhase) {
//        nodes.node[index].carPhase = 0.0;
//    }
//    
//    nodes.node[index].modPhase += nodes.node[index].modStep * nodes.mov;    //Modulater
//    if(M_2XPI < nodes.node[index].modPhase) {
//        nodes.node[index].modPhase = 0.0;
//    }
//    
//    phase = (sin(nodes.node[index].carPhase) + sin(nodes.node[index].modPhase)) * TREMOR_RATIO;   // -0.5 to 0.5
//}
//
//
//
///////////////////// UPDATE POSITION /////////////////////
//void AgentMotion::updatePosition(int index) {
//    // Update Position
//    ofVec2f nextPos;
//    nodeX = (nodes.node[index].velocityX * phase + nodes.node[index].x * STAY_RATIO) * nodes.size;
//    nodeY = (nodes.node[index].velocityY * phase + nodes.node[index].y * STAY_RATIO) * nodes.size;
//    
//    //Position on Screen
//    nextPos.x = (nodeX * CANVAS_HEIGHT) + (nodes.scale_x * CANVAS_HEIGHT * *width_rate);
//    nextPos.y = (nodeY + nodes.scale_y) * CANVAS_HEIGHT;
//    
//    nodePos[index] = nextPos; //Set position onto Array
//}
//
///////////////////// UPDATE /////////////////////
//
//void AgentMotion::update() {
//    // Update Node, Position Array
//    for(int i = 0; i < nodes.nodeNum; i++) {
//        // on each node
//        updatePhase(i);
//        updatePosition(i);
//    }
//    
//    // Update VBO
//    nodeVbo.updateVertexData(nodePos, nodes.nodeNum);
//    lineVbo.updateVertexData(nodePos, nodes.nodeNum);
//}
//
//
//void AgentMotion::updateColors() {
//    for(int i = 0; i < lineNum; i++) {
//        if (i < NODES_MAX) {
//            //Node
//            nodeColors[i] = ofFloatColor(grayScale);
//        }
//        //Line
//        lineColors[i] = ofFloatColor(grayScale);
//    }
//    
//    nodeVbo.updateColorData(nodeColors, nodes.nodeNum);
//    lineVbo.updateColorData(lineColors, lineNum);
//}
//
///////////////////// INIT /////////////////////
//
//void AgentMotion::initModulation(int index) {
//    ofVec2f vel = ofVec2f(frand() * 2.0 - 1.0, frand() * 2.0 - 1.0).getNormalized();
//    
//    nodes.node[index].velocityX = vel.x;
//    nodes.node[index].velocityY = vel.y;
//    
//    //nodes.node[index].modStep = ofRandom(STEP_MIN, STEP_MAX);
//    //nodes.node[index].carStep = ofRandom(STEP_MIN, STEP_MAX);
//    
//    nodes.node[index].modStep = (STEP_MAX - STEP_MIN) * frand() + STEP_MIN;
//    nodes.node[index].carStep = (STEP_MAX - STEP_MIN) * frand() + STEP_MIN;
//    
//    nodes.node[index].modPhase = 0.0;
//    nodes.node[index].carPhase = 0.0;
//}
//
//float AgentMotion::getPointSize() {
//    float pointSize = 3.5;
//    if(nodes.size < 0.02) {
//        pointSize = 2.0;
//    } else if (0.02 <= nodes.size && nodes.size < 0.03) {
//        pointSize = 2.0;
//    } else if(0.03 <= nodes.size && nodes.size < 0.04) {
//        pointSize = 2.5;
//    } else if(0.04 <= nodes.size && nodes.size < 0.05) {
//        pointSize = 3.0;
//    } else {
//        pointSize += 8.0 * nodes.size;
//    }
//    
//    return pointSize;
//}
//
//float AgentMotion::getLineWidth() {
//    float lineWidth = 0.5;
//    if(nodes.size <= 0.01) {
//        lineWidth = 0.05;
//    } else if (0.01 < nodes.size && nodes.size < 0.02) {
//        lineWidth = 0.1;
//    } else if(0.02 <= nodes.size && nodes.size < 0.05) {
//        lineWidth = 0.25;
//    }
//    
//    return lineWidth;
//}
//

