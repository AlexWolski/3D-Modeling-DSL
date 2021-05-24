#include "MeshNode.h"

MeshNode::MeshNode()
{
	mesh = make_shared<ofMesh>(ofMesh::box(100.0f, 100.0f, 100.0f));
}

/// <summary></summary>
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
	ofMesh& meshRef = *mesh.get();
	ofGetCurrentRenderer()->draw(meshRef, OF_MESH_FILL);
}