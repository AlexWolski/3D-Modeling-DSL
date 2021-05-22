#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp
{
private:
	ofEasyCam easyCam;
	ofLight keyLight, backLight;

	ofMaterial whiteDiffuse;

	ofBoxPrimitive box;
	ofxAssimpModelLoader fox;

public:
	void setup();
	void update();
	void draw();
};
