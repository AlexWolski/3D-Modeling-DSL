#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{
private:
	ofEasyCam easyCam;
	ofLight keyLight, backLight;

	ofMaterial whiteDiffuse;

	ofBoxPrimitive box;

public:
	void setup();
	void update();
	void draw();
};
