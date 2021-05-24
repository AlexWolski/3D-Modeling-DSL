#pragma once

#include <fstream>
#include <sstream>
#include "ofMain.h"
#include "MeshNode.h"
#include "SampleModels.h"
#include "Parser.h"
#include "Interpreter.h"

namespace ModelScript
{
	class ofApp : public ofBaseApp
	{
	private:
		ofEasyCam easyCam;
		ofLight keyLight, backLight;

		shared_ptr<MeshNode> model;

		void initializeScene();
		static std::string loadFile(std::string filePath);
		static shared_ptr<MeshNode> generateModel(std::string script);

	public:
		void setup();
		void draw();
	};
}
