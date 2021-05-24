#include "MeshNode.h"

namespace ModelScript
{
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

	/// <summary>Create a deep copy of the given mesh node</summary>
	/// <remarks>Does not need to implement the copy and swap idiom as there are very few data members</remarks>
	MeshNode::MeshNode(const MeshNode& otherNode)
	{
		*this = otherNode;
	}

	/// <summary>Deeply copy the values of the given mesh node</summary>
	MeshNode& MeshNode::operator=(const MeshNode& otherNode)
	{
		//Call the base assignment operator
		ofNode::operator=(otherNode);

		//Copy the material and mesh
		material = otherNode.material;

		if (otherNode.mesh == nullptr)
			mesh = nullptr;
		else
			mesh = make_shared<ofMesh>(*otherNode.mesh);

		children.clear();

		//Iteratively copy and add the children of the other node
		//The 'this' keyword is used because shared_from_this is not yet defined in the constructor
		for (shared_ptr<MeshNode> otherChild : otherNode.children)
		{
			shared_ptr<MeshNode> otherChildCopy = make_shared<MeshNode>(*otherChild);
			otherChildCopy->ofNode::setParent(*this);
			children.push_back(otherChildCopy);
		}

		return *this;
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
		ofNode::setParent(*parent);
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
		ofGetCurrentRenderer()->draw(*mesh, OF_MESH_FILL);
		material.end();
	}
}