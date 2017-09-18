#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"

class ofApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
    void drawPointCloud(int i);
    void loadMeshSequence();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
		
    ofFbo fbo;
    ofCamera camera;
    vector<ofMesh> meshes;
    int renderWidth;
    int renderHeight;
    string folder;
    string prefixPath;
    string loadPath;
    int meshNumber;
    bool render;
    ofxDelaunay triangulation;

};
