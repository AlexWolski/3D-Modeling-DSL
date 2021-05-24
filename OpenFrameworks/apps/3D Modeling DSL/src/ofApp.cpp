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

	box = make_shared<MeshNode>();

	//Creating material
	whiteDiffuse.setDiffuseColor(ofColor::white);
}

void ofApp::update()
{

}

void ofApp::draw()
{
	easyCam.begin();
	whiteDiffuse.begin();
	box->rotateDeg(5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	box->draw();
	shared_ptr<MeshNode> test = make_shared<MeshNode>();
	test->move(0.0f, 50.0f, 0.0f);
	test->setScale(0.5f, 0.5f, 0.5f);
	test->setParent(box);
	whiteDiffuse.end();
	easyCam.end();
}