#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofColor color;
	glm::vec3 noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int i = 0; i < 100; i++) {

		auto location_1 = this->getLocationOnSphere(300, noise_param.x + i * 0.003);
		auto location_2 = this->getLocationOnSphere(300, noise_param.y + i * 0.003);

		color.setHsb(ofMap(i, 0, 100, 0, 255), 200, 255);
		ofSetColor(color);

		ofDrawLine(location_1, location_2);
		ofDrawCircle(location_1, 2.5);
		ofDrawCircle(location_2, 2.5);
	}

	this->cam.end();

	/*
	int start = 30;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
glm::vec3 ofApp::getLocationOnSphere(float radius, float noise_param) {

	float phi = ofMap(ofNoise(noise_param, ofGetFrameNum() * 0.005), 0, 1, 0, 4 * PI);
	float theta = ofMap(ofNoise(noise_param, ofGetFrameNum() * 0.005), 0, 1, 0, 2 * PI);

	float x = radius * sin(theta) * cos(phi);
	float y = radius * sin(theta) * sin(phi);
	float z = radius * cos(theta);

	return glm::vec3(x, y, 0);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}