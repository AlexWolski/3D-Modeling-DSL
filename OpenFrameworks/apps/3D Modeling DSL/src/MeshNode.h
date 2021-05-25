#pragma once

#include <memory>
#include <vector>
#include "ofNode.h"
#include "of3dPrimitives.h"
#include "ofxAssimpModelLoader.h"

using namespace std;

namespace ModelScript
{
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
		MeshNode(std::string modelPath);
		MeshNode(const MeshNode& otherNode);

		MeshNode& operator=(const MeshNode& otherNode);

		shared_ptr<MeshNode> getPointer();
		void addChild(shared_ptr<MeshNode> child);
		void setParent(shared_ptr<MeshNode> parent);
		void setMesh(shared_ptr<ofMesh> mesh);
		void setColor(ofColor color);

		void draw();
		void customDraw() override;

	private:
		static shared_ptr<ofMesh> loadPrimitive(PrimitiveType type);
		static shared_ptr<ofMesh> loadModel(std::string modelPath);

		ofMaterial material;
		shared_ptr<ofMesh> mesh = nullptr;
		vector<shared_ptr<MeshNode>> children;
	};
}