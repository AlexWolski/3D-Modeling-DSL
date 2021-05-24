#pragma once

#include "ofMain.h"
#include "ObjectNode.h"

class ofApp : public ofBaseApp
{
private:
	ofEasyCam easyCam;
	ofLight keyLight, backLight;
	ofMaterial whiteDiffuse;

	ObjectNode box;

public:
	void setup();
	void update();
	void draw();
};
