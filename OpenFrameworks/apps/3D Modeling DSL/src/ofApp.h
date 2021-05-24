#pragma once

#include <fstream>
#include <sstream>
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
		static string loadFile(string filePath);

	public:
		void setup();
		void draw();
	};
}
