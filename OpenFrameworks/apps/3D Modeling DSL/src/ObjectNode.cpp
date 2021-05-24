#include "ObjectNode.h"

/// <summary></summary>
shared_ptr<ObjectNode> ObjectNode::getPointer()
{
	return shared_from_this();
}

/// <summary>Moves the object and its children by an offset</summary>
void ObjectNode::translate(float x, float y, float z)
{
	ofNode::move(x, y, z);
}

/// <summary>Rotates the object on the x, y, and z axes by the given angles (in degrees.)</summary>
void ObjectNode::rotate(float x, float y, float z)
{
	ofNode::tiltDeg(x);
	ofNode::panDeg(y);
	ofNode::rollDeg(z);
}

/// <summary>Scales each axis of the object by a percentage of the original scale</summary>
void ObjectNode::scale(float x, float y, float z)
{
	ofNode::setScale(x, y, z);
}

/// <summary>Add a child object node that inherits this object's transform stack</summary>
void ObjectNode::addChild(shared_ptr<ObjectNode> child)
{
	children.push_back(child);
}

/// <summary>Inherit the transform stack of the given object node</summary>
void ObjectNode::setParent(shared_ptr<ObjectNode> parent)
{
	parent->addChild(getPointer());
	ofNode& parentNode = *(parent.get());
	ofNode::setParent(parentNode);
}

/// <summary>Draw all child objects</summary>
void ObjectNode::draw()
{
	for (shared_ptr<ObjectNode> childNode : children)
		childNode->draw();
}



/// <summary>Converts a primitive type into an openFrameworks object</summary>
of3dPrimitive PrimitiveObject::typeToObject(Type type)
{
	switch (type)
	{
	case Type::Plane:
		return ofBoxPrimitive();
		break;

	case Type::Sphere:
		return ofSpherePrimitive();
		break;

	case Type::IcoSphere:
		return ofIcoSpherePrimitive();
		break;

	case Type::Cylinder:
		return ofCylinderPrimitive();
		break;

	case Type::Cone:
		return ofConePrimitive();
		break;

	case Type::Box:
		return ofBoxPrimitive();
		break;

	default:
		throw "There is no primitive shape with type: " + type;
	}
}

/// <summary>Instantiates an object node containing a primitive model</summary>
PrimitiveObject::PrimitiveObject(Type type)
{
	ObjectNode::draw();
	primitive = typeToObject(type);
}

/// <summary>Draws the primitive model</summary>
void PrimitiveObject::draw()
{
	ObjectNode::draw();
	primitive.drawFaces();
}



/// <summary>Instantiates an object node containing a 3D model</summary>
ModelObject::ModelObject(string modelPath)
{
	model.loadModel(modelPath);
}

/// <summary>Draws the 3D model</summary>
void ModelObject::draw()
{
	model.drawFaces();
}