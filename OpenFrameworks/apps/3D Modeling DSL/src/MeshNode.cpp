#include "MeshNode.h"

MeshNode::MeshNode()
{
	mesh = nullptr;
}

/// <summary>Instantiate a mesh node with a custom model</summary>
MeshNode::MeshNode(PrimitiveType type)
{
	setMesh(loadPrimitive(type));
}

/// <summary>Instantiate a mesh node with a primitive model</summary>
MeshNode::MeshNode(string modelPath)
{
	setMesh(loadModel(modelPath));
}

/// <summary>Returns a pointer to this object</summary>
shared_ptr<MeshNode> MeshNode::getPointer()
{
	return shared_from_this();
}

/// <summary>Add a child object node that inherits this object's transform stack</summary>
void MeshNode::addChild(shared_ptr<MeshNode> child)
{
	children.push_back(child);
}

/// <summary>Inherit the transform stack of the given object node</summary>
void MeshNode::setParent(shared_ptr<MeshNode> parent)
{
	parent->addChild(getPointer());
	ofNode& parentNode = *(parent.get());
	ofNode::setParent(parentNode);
}

void MeshNode::setMesh(shared_ptr<ofMesh> mesh)
{
	this->mesh = mesh;
}

void MeshNode::setColor(ofColor color)
{
	material.setDiffuseColor(color);
}

/// <summary>Instantiate a model of the specified primitive type</summary>
shared_ptr<ofMesh> MeshNode::loadPrimitive(PrimitiveType type)
{
	ofMesh primitiveMesh;

	switch (type)
	{
	case PrimitiveType::Plane:
		primitiveMesh = ofMesh::plane(100.0f, 100.0f, 2);
		break;
	case PrimitiveType::Sphere:
		primitiveMesh = ofMesh::sphere(100.0f);
		break;
	case PrimitiveType::IcoSphere:
		primitiveMesh = ofMesh::icosphere(100.0f);
		break;
	case PrimitiveType::Cylinder:
		primitiveMesh = ofMesh::cylinder(100.0f, 100.0f, 12);
		break;
	case PrimitiveType::Cone:
		primitiveMesh = ofMesh::cone(100.0f, 100.0f, 12);
		break;
	case PrimitiveType::Box:
		primitiveMesh = ofMesh::box(100.0f, 100.0f, 100.0f);
		break;
	}

	return make_shared<ofMesh>(primitiveMesh);
}

/// <summary>Load the model at the given file path</summary>
shared_ptr<ofMesh> MeshNode::loadModel(string modelPath)
{
	//Load the 3D model
	ofxAssimpModelLoader ml;
	ml.loadModel(modelPath);

	//Create a shared pointer to the model mesh
	ofMesh customMesh = ml.getMesh(0);
	shared_ptr<ofMesh> modelPointer = make_shared<ofMesh>(customMesh);

	return modelPointer;
}

/// <summary>Draw the mesh and all children meshes with the proper transform</summary>
void MeshNode::draw()
{
	if (mesh != nullptr)
		ofGetCurrentRenderer()->draw(*this);

	for (shared_ptr<MeshNode> childNode : children)
		childNode->draw();
}

/// <summary>Draw the mesh without transforms</summary>
void MeshNode::customDraw()
{
	material.begin();

	ofMesh& meshRef = *mesh.get();
	ofGetCurrentRenderer()->draw(meshRef, OF_MESH_FILL);

	material.end();
}