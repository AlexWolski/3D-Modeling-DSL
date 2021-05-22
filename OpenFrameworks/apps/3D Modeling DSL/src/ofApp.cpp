#include "ofApp.h"

void ofApp::setup()
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

	//Creating material
	whiteDiffuse.setDiffuseColor(ofColor::white);

	//Load the fox model
	fox.loadModel("fox.obj");
	fox.setRotation(0, 180, 1, 0, 0);
	fox.setScale(0.4, 0.4, 0.4);
	fox.setPosition(-150.0f, -40.0f, 0.0f);
}

void ofApp::update()
{

}

void ofApp::draw()
{
	easyCam.begin();
	whiteDiffuse.begin();
	box.draw();
	fox.drawFaces();
	whiteDiffuse.end();
	easyCam.end();
}