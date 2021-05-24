#pragma once

#include "ofMain.h"
#include "MeshNode.h"
#include "SampleModels.h"

class ofApp : public ofBaseApp
{
private:
	ofEasyCam easyCam;
	ofLight keyLight, backLight;

	shared_ptr<MeshNode> model;

public:
	void setup();
	void update();
	void draw();
};
