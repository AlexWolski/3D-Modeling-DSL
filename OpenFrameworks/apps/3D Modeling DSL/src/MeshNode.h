#pragma once

#include <memory>
#include <vector>
#include "ofNode.h"
#include "of3dPrimitives.h"
#include "ofxAssimpModelLoader.h"

using namespace std;

enum class PrimitiveType
{
	Plane, Sphere, IcoSphere, Cylinder, Cone, Box
};

//A node representing a transform and a list of objects inheriting that transform
class MeshNode :
	public ofNode,
	public enable_shared_from_this<MeshNode>
{
public:
	MeshNode();
	MeshNode(PrimitiveType type);
	MeshNode(string modelPath);

	void draw();
	void customDraw() override;

	shared_ptr<MeshNode> getPointer();
	void addChild(shared_ptr<MeshNode> child);
	void setParent(shared_ptr<MeshNode> parent);
	void setMesh(shared_ptr<ofMesh> mesh);

private:
	static shared_ptr<ofMesh> loadPrimitive(PrimitiveType type);
	static shared_ptr<ofMesh> loadModel(string modelPath);

	shared_ptr<ofMesh> mesh;
	vector<shared_ptr<MeshNode>> children;
};