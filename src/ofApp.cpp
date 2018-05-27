#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Circle setup
    ofSetCircleResolution(100);
    
    //Loading sounds
    base.load("sounds/1085.mp3");
    synth.load("sounds/synth.wav");
    vocals.load("sounds/violet.mp3");
    
    //Multiplay
    base.setMultiPlay(false);
    vocals.setMultiPlay(true);
    
    //Buttons setup
    btnF.set(0,0,ofGetWidth(),ofGetHeight());
    btnW = ofGetWidth()/6;
    btnH = ofGetHeight()/6;
    btnL.set(btnW,btnH,btnW*2,btnH*4);
    btnR.set(btnW*3,btnH,btnW*2,btnH*4);
    
    //Fonts setup
    font.load("fonts/Sudbury_Basin_3D.ttf", 50);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //Update the sound playing system:
    ofSoundUpdate();
    
    //Spectrum
    spectrum=ofSoundGetSpectrum(NUM);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Draw buttons
    ofDrawRectangle(btnF);
    ofDrawRectangle(btnR);
    ofDrawRectangle(btnL);
    
    //Background gradient
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex3f( 0, 0, 0);
    glVertex3f( ofGetWidth(), 0, 0);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex3f( ofGetWidth(), ofGetHeight(), 0);
    glVertex3f( 0, ofGetHeight(), 0);
    glEnd();
    
    //Base
    ofSetColor(0);
    float baseW = font.stringWidth("bass");
    float btnFW = ofGetWidth()- baseW;
    font.drawString("bass", btnFW/2, 100);
    //Base playing
    if (base.isPlaying()) {
        ofBackground(66, 66, 66);
        //Text
        ofSetColor(246, 211, 101);
        font.drawString("bass", btnFW/2, 100);
    }
    
    //Buttons gradient
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(btnW, btnH, 0);
    glVertex3f( btnW*5, btnH, 0);
    glColor3f(0.2f,0.2f,0.2f);
    glVertex3f( btnW*5, btnH*5, 0);
    glVertex3f( btnW, btnH*5, 0);
    glEnd();
    
    //Synth
    ofSetColor(0);
    float synthW = font.stringWidth("synth");
    float btnLW = btnW - synthW/2;
    font.drawString("synth", btnW + btnLW*0.9, btnH+100);
    //Synth playing
    if (synth.isPlaying()) {
        //Gradient
        glBegin(GL_QUADS);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3f( btnW, btnH, 0);
        glVertex3f( btnW*3, btnH, 0);
        glColor3f(0.3f, 0.3f, 0.3f);
        glVertex3f( btnW*3, btnH*5, 0);
        glVertex3f( btnW, btnH*5, 0);
        glEnd();
        //Text
        ofSetColor(161,196,253);
        font.drawString("synth", btnW + btnLW*0.9, btnH+100);
    }
    
    //Vocals
    ofSetColor(0);
    float vocalsW = font.stringWidth("vocals");
    float btnRW = btnW - vocalsW/2;
    font.drawString("vocals", btnW*3 + btnRW*0.9, btnH+100);
    //Vocals playing
    if (vocals.isPlaying()) {
        //Gradient
        glBegin(GL_QUADS);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3f( btnW*3, btnH, 0);
        glVertex3f( btnW*5, btnH, 0);
        glColor3f(0.3f, 0.3f, 0.3f);
        glVertex3f( btnW*5, btnH*5, 0);
        glVertex3f( btnW*3, btnH*5, 0);
        glEnd();
        //Text
        ofSetColor(212, 252, 121);
        font.drawString("vocals", btnW*3 + btnRW*0.9, btnH+100);
    }
    
    //Draw circles
    for(int i =0; i<circlePos.size();i++){
        float radius = ofMap(spectrum[i],0,10,10,500);
        ofSetColor(circleColor[i]);
        ofDrawCircle(circlePos[i],radius);
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    // Control the speed of the base via drag, within its region
    if (btnF.inside(x,y) && !btnL.inside(x,y) && !btnR.inside(x,y)){
        base.setSpeed( 0.5f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*1.0f);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    ofColor newColor;
    //Base button
    if (btnF.inside(x,y) && !btnL.inside(x,y) && !btnR.inside(x,y)) {
        base.setLoop(true);
        base.play();
        //Color
        newColor.set(246, 211, 101,127);
    }
    
    //Synth button
    if (btnL.inside(x,y)){
        synth.play();
        synth.setSpeed( 0.1f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*10);
        //Map x within the left button to -1 to 1 ( for left / right panning )
        synth.setPan(ofRandom(-1,1));
        //Color
        newColor.set(161,196,253,127);
    }
    
    //Vocals button
    if (btnR.inside(x,y)){
        vocals.play();
        vocals.setSpeed( 0.1f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*3);
        //Map x within the right button to -1 to 1 ( for left / right panning )
        vocals.setPan(ofRandom(-1,1));
        //Color
        newColor.set(212,252,121,127);
    }
    
    //Color vector
    circleColor.push_back(newColor);
    
    //Circle vector
    ofVec2f newCircle = ofVec2f(x,y);
    circlePos.push_back(newCircle);

    
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
