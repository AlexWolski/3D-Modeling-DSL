#pragma once

#include <memory>
#include <vector>
#include "ofNode.h"
#include "of3dPrimitives.h"
#include "ofxAssimpModelLoader.h"

using namespace std;

//A node representing a transform and a list of objects inheriting that transform
class ObjectNode : ofNode
{
public:
	enum PrimitiveType
	{
		Plane, Sphere, IcoSphere, Cylinder, Cone, Box
	};

	static of3dPrimitive typeToObject(PrimitiveType type);

	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);

	void addChild(shared_ptr<ObjectNode> child);
	void setParent(shared_ptr<ObjectNode> parent);

	virtual void draw();

protected:
	vector<shared_ptr<ObjectNode>> children;
};


//An object node containing an openFrameworks primitive object
class PrimitiveObject : ObjectNode
{
private:
	of3dPrimitive primitive;

public:
	PrimitiveObject(PrimitiveType type);

	void draw();
};


//An object node containing an openFrameworks model object
class ModelObject : ObjectNode
{
private:
	ofxAssimpModelLoader model;

public:
	ModelObject(string modelPath);

	void draw();
};