#include "ofApp.h"

namespace ModelScript
{
	/// <summary>Set the light, camera, and video settings</summary>
	void ofApp::initializeScene()
	{
		//Set the video settings.
		ofSetVerticalSync(true);
		ofSetFrameRate(60);
		//Set the background to black.
		ofBackground(0);

		//Set the camera settings
		ofEnableDepthTest();
		easyCam.setupPerspective(false, 45);
		easyCam.setPosition({ 0.0f, 0.0f, 500.0f });
		easyCam.setTarget({ 0.0f, 0.0f, 0.0f });

		//Light settings
		keyLight.setDirectional();
		keyLight.setOrientation({ 210.0f, -15.0f, 0.0f });
		keyLight.setDiffuseColor(ofFloatColor::white);
		keyLight.setAmbientColor(ofFloatColor::darkGray);
		keyLight.enable();

		backLight.setDirectional();
		backLight.setOrientation({ 15.0f, 15.0f, 0.0f });
		backLight.setDiffuseColor(ofFloatColor::grey);
		backLight.enable();
	}

	/// <summary>Reads in a file and returns the contents in a string</summary>
	std::string ofApp::loadFile(std::string filePath)
	{
		ifstream scriptFile(filePath);
		stringstream buffer;

		if (!scriptFile.is_open())
			throw "Unable to open file: '" + filePath + "'";

		buffer << scriptFile.rdbuf();
		std::string fileContents = buffer.str();

		return fileContents;
	}

	/// <summary>Procedurally generates a model object from the given model script</summary>
	shared_ptr<MeshNode> ofApp::generateModel(std::string scriptFile)
	{
		//Read the script from file
		std::string scriptContents = loadFile(scriptFile);
		//Parse the script into an AST
		unique_ptr<node> AstRoot = Parser::parseScript(scriptContents.c_str());
		//Interpret the AST and generate a model
		shared_ptr<MeshNode> model = Interpreter::execute(move(AstRoot));

		return model;
	}

	void ofApp::setup()
	{
		initializeScene();

		//Create a house model that is 4 rooms wide and 2 stories high
		model = SampleModels::houseModel(3, 2);
		//model = generateModel("data/Scripts/test1.ms");
	}

	void ofApp::draw()
	{
		easyCam.begin();
		model->draw();
		easyCam.end();
	}
}