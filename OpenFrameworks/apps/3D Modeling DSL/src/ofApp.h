#pragma once

#include "ofMain.h"
#include "MeshNode.h"
#include "SampleModels.h"

namespace ModelScript
{
	class ofApp : public ofBaseApp
	{
	private:
		ofEasyCam easyCam;
		ofLight keyLight, backLight;

		shared_ptr<MeshNode> model;

		void initializeScene();

	public:
		void setup();
		void update();
		void draw();
	};
}
