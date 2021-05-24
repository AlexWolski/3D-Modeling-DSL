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

	void ofApp::setup()
	{
		initializeScene();

		//Create a house model that is 4 rooms wide and 2 stories high
		model = SampleModels::houseModel(3, 2);
	}

	void ofApp::draw()
	{
		easyCam.begin();
		model->draw();
		easyCam.end();
	}
}