#pragma once

#include "ofMain.h"
#include "MeshNode.h"

class ofApp : public ofBaseApp
{
private:
	ofEasyCam easyCam;
	ofLight keyLight, backLight;
	ofMaterial whiteDiffuse;

	shared_ptr<MeshNode> box;

public:
	void setup();
	void update();
	void draw();
};
