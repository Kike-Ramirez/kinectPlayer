#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
    ofSetSphereResolution(60);
    ofEnableSmoothing();

    // Set folder to render
    folder = "20_42";

    render = true;

    //some path, may be absolute or relative to bin/data
    string path = folder;
    ofDirectory dir(path);
    //only show png files
    dir.allowExt("ply");
    //populate the directory object
    dir.listDir();

    // Set file names from folder name
    prefixPath = "mesh_" + folder + "_";
    loadPath = "./" + folder + "/" + prefixPath;
    meshNumber = 3; //dir.size();

    renderWidth = 1920;
    renderHeight = 1080;
		
    fbo.allocate(renderWidth, renderHeight, GL_RGBA );
	
    ofSetFrameRate(30);

    // Load meshes (it may take a while, better do it before)
    loadMeshSequence();
	
}

//--------------------------------------------------------------
void ofApp::update() {
	

    // Update mesh drawn

    // Update camera position
//    float rotateAmount = ofMap(ofGetFrameNum(), 0, meshNumber , 0, 360);

//    ofVec3f center = ofVec3f(0, 0, 0);

//    ofVec3f furthestPoint = ofVec3f(0, 0, 20);


//    ofVec3f directionToFurthestPoint = (furthestPoint - center);
//    ofVec3f directionToFurthestPointRotated = directionToFurthestPoint.getRotated(rotateAmount, ofVec3f(0,1,0));
//    camera.lookAt(center + directionToFurthestPointRotated);
//    camera.setPosition(center);
//    camera.setFov(40);

}

//--------------------------------------------------------------
void ofApp::draw() {
	
    ofBackground(100, 100, 100);

    if (ofGetFrameNum() > meshNumber) ofExit();

    // Draw mesh into image
    fbo.begin();
    //camera.begin();
    ofBackground(0, 0);
    drawPointCloud( ofGetFrameNum() );
    //camera.end();
    fbo.end();

    // Save Image in data file
    if (render) {

        ofImage image;
        image.allocate( renderWidth, renderHeight, OF_IMAGE_COLOR_ALPHA );
        ofPixels pixels;
        pixels.allocate( renderWidth, renderHeight, OF_IMAGE_COLOR_ALPHA );
        ofTexture texture;
        texture = fbo.getTexture();
        texture.readToPixels(pixels);
        image.setFromPixels(pixels);
        string savePath = "./Frames/" + folder + "_b/" + prefixPath + ofToString( ofGetFrameNum() ) + ".png";

        image.save(savePath);
    }

    ofSetColor(255);
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    string complete = ofToString(float(ofGetFrameNum())/meshNumber * 100) + "%";
    ofDrawBitmapString(complete, 20, 30);

    fbo.draw(0, 0, ofGetWidth(), ofGetHeight() );

}

void ofApp::drawPointCloud(int i) {


    ofMesh mesh = meshes[i];
    float scale = 1;

    ofPushMatrix();
    float radio = ofMap(ofGetFrameNum(), 0, meshNumber, -300, -150);
    float upLevel = ofMap(ofGetFrameNum(), 0, meshNumber, 200, 0);
    ofTranslate(renderWidth * 0.5, renderHeight * 0.5 + upLevel, radio);
    float rotateAmount = ofMap(ofGetFrameNum(), 0, meshNumber , -30, 0 );
    ofRotateY(rotateAmount);
    ofScale(scale, scale, -scale);

    triangulation.reset();

    for (int i = 0; i < mesh.getNumVertices(); i= i + 6 ) {
        ofPushMatrix();

        ofVec3f point = mesh.getVertex(i);
        point = point - ofVec3f(0, 0, 950);
        ofTranslate(point);
        ofColor color = mesh.getColor(i);
        ofPoint point2 = ofPoint(0, 0, 500);
        ofSetColor(color, 100);
        ofSetLineWidth(3);
        ofDrawLine(point, point2);
        ofSetColor(color);
        //ofDrawSphere(point, 3);

        triangulation.addPoint(point);

        ofPopMatrix();
    }

    for (int i = 0; i < mesh.getNumVertices(); i= i + 6 ) {
        ofPushMatrix();

        ofVec3f point = mesh.getVertex(i);
        point = point - ofVec3f(0, 0, 950);
        ofTranslate(point);
        ofColor color = mesh.getColor(i);
        ofSetColor(color);
        ofDrawSphere(point, 3);

        //triangulation.addPoint(point);
        ofPopMatrix();
    }
    ofSetColor(255);

    triangulation.triangulate();
    ofNoFill();
    triangulation.draw();
    ofFill();
    ofPopMatrix();

//    ofSetColor(255);
    //glPointSize(3);
//    ofPushMatrix();
    // the projected points are 'upside down' and 'backwards'
    // float scale = 1;
    // float rotateAmount = ofMap(ofGetFrameNum(), 0, 100 , 0, 360);
    // ofRotateY(rotateAmount);

    // ofTranslate(renderWidth * 0.5, renderHeight * 0.5, -100); // center the points a bit

    // ofScale(scale, -scale, -scale);


    //ofEnableDepthTest();
    // mesh.drawVertices();
    //ofDisableDepthTest();
//    ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::loadMeshSequence() {

    meshes.clear();

    for (int i = 0; i < meshNumber; i++) {

        string path = loadPath + ofToString(i) + ".ply";
        ofMesh mesh;
        mesh.load(path);
        mesh.enableColors();
        meshes.push_back(mesh);

        cout << "Cargando mesh " << ofToString(i) << endl;

    }


}


//--------------------------------------------------------------
void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::keyPressed (int key) {
	switch (key) {
			
//		case '>':
//		case '.':
//            farThreshold += 10;
//            if (farThreshold > 11000) farThreshold = 11000;
//			break;
			
//		case '<':
//		case ',':
//            farThreshold -= 10;
//            if (farThreshold < nearThreshold) farThreshold = nearThreshold;
//			break;
			
//		case '+':
//		case '=':
//            nearThreshold += 10;
//            if (nearThreshold > farThreshold) nearThreshold = farThreshold;
//			break;
			
//		case '-':
//            nearThreshold -= 10;
//			if (nearThreshold < 0) nearThreshold = 0;
//			break;
			
//		case 'w':
//			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
//			break;
			
//		case 'o':
//			kinect.setCameraTiltAngle(angle); // go back to prev tilt
//			kinect.open();
//			break;
			
//		case 'c':
//			kinect.setCameraTiltAngle(0); // zero the tilt
//			kinect.close();
//			break;
			
//		case '1':
//			kinect.setLed(ofxKinect::LED_GREEN);
//			break;
			
//		case '2':
//			kinect.setLed(ofxKinect::LED_YELLOW);
//			break;
			
//		case '3':
//			kinect.setLed(ofxKinect::LED_RED);
//			break;
			
//		case '4':
//			kinect.setLed(ofxKinect::LED_BLINK_GREEN);
//			break;
			
//		case '5':
//			kinect.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
//			break;
			
//		case '0':
//			kinect.setLed(ofxKinect::LED_OFF);
//			break;

//        case ' ':
//            recording = !recording;
//            if (!recording) saveMeshSequence();
//            break;

//		case OF_KEY_UP:
//			angle++;
//			if(angle>30) angle=30;
//			kinect.setCameraTiltAngle(angle);
//			break;
			
//		case OF_KEY_DOWN:
//			angle--;
//			if(angle<-30) angle=-30;
//			kinect.setCameraTiltAngle(angle);
//			break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}
