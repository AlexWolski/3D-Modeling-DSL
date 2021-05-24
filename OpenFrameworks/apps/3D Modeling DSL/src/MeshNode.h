#pragma once

#include <memory>
#include <vector>
#include "ofNode.h"
#include "of3dPrimitives.h"
#include "ofxAssimpModelLoader.h"

using namespace std;

//A node representing a transform and a list of objects inheriting that transform
class MeshNode :
	public ofNode,
	public enable_shared_from_this<MeshNode>
{
public:
	MeshNode();

	shared_ptr<MeshNode> getPointer();
	void draw();
	void customDraw();

	void addChild(shared_ptr<MeshNode> child);
	void setParent(shared_ptr<MeshNode> parent);

protected:
	shared_ptr<ofMesh> mesh;
	vector<shared_ptr<MeshNode>> children;
};