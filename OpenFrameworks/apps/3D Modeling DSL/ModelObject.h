#pragma once

#include <memory>
#include <vector>
#include "ofNode.h"
#include "of3dPrimitives.h"
#include "ofxAssimpModelLoader.h"

using namespace std;

class ModelObject : ofNode
{
	enum PrimitiveType
	{
		Plane, Sphere, IcoSphere, Cylinder, Cone, Box
	};

private:
	of3dPrimitive primitive;
	ofxAssimpModelLoader model;
	vector<shared_ptr<ModelObject>> children;

	of3dPrimitive typeToObject(PrimitiveType type);

public:
	ModelObject(PrimitiveType type);
	ModelObject(string modelPath);

	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);

	void addChild(shared_ptr<ModelObject> child);
	void setParentTest(shared_ptr<ModelObject> parent);

	void draw();
};

ModelObject::ModelObject(PrimitiveType type)
{
	primitive = typeToObject(type);
}

ModelObject::ModelObject(string modelPath)
{
	model.loadModel(modelPath);
}

of3dPrimitive ModelObject::typeToObject(PrimitiveType type)
{
	switch (type)
	{
	case PrimitiveType::Plane:
		return ofBoxPrimitive();
		break;

	case PrimitiveType::Sphere:
		return ofSpherePrimitive();
		break;

	case PrimitiveType::IcoSphere:
		return ofIcoSpherePrimitive();
		break;

	case PrimitiveType::Cylinder:
		return ofCylinderPrimitive();
		break;

	case PrimitiveType::Cone:
		return ofConePrimitive();
		break;

	case PrimitiveType::Box:
		return ofBoxPrimitive();
		break;

	default:
		throw "There is no primitive shape with type: " + type;
	}
}

void ModelObject::addChild(shared_ptr<ModelObject> child)
{
	children.push_back(child);
	shared_ptr<ModelObject> selfPointer = make_shared<ModelObject>(this);
	child->setParentTest(selfPointer);
}

void ModelObject::setParentTest(shared_ptr<ModelObject> parent)
{
	ofNode& parentNode = *(parent.get());
	setParent(parentNode);
}

void ModelObject::draw()
{

}