#pragma once

#include "MeshNode.h"

class SampleModels
{
public:
	static shared_ptr<MeshNode> houseModel(int roomsPerStory, int numStories)
	{
		shared_ptr<MeshNode> house = make_shared<MeshNode>();

		//Iteratively add rooms and floors
		for (int currentFloor = 0; currentFloor < numStories; currentFloor++)
		{
			float floorOffset = 100.f * currentFloor;

			shared_ptr<MeshNode> story = make_shared<MeshNode>();
			story->setParent(house);
			story->move(0.0f, floorOffset, 0.0f);

			for (int currentRoom = 0; currentRoom < roomsPerStory; currentRoom++)
			{
				float roomOffset = 100.f * currentRoom - 100.0f;

				shared_ptr<MeshNode> room = make_shared<MeshNode>();
				room->setParent(story);
				room->move(roomOffset, 0.0f, 0.0f);

				//Define a room
				shared_ptr<MeshNode> leftWall = make_shared<MeshNode>(PrimitiveType::Box);
				leftWall->setParent(room);
				leftWall->setColor(ofColor::black);
				leftWall->setScale(0.05f, 0.95f, 0.95f);
				leftWall->move(-50.f, 0.0f, 0.0f);

				shared_ptr<MeshNode> rightWall = make_shared<MeshNode>(PrimitiveType::Box);
				rightWall->setParent(room);
				rightWall->setColor(ofColor::black);
				rightWall->setScale(0.05f, 0.95f, 0.95f);
				rightWall->move(50.f, 0.0f, 0.0f);

				shared_ptr<MeshNode> backWall = make_shared<MeshNode>(PrimitiveType::Box);
				backWall->setParent(room);
				backWall->setColor(ofColor::white);
				backWall->setScale(1.05f, 1.05f, 0.05f);
				backWall->move(0.0f, 0.0f, -50.f);

				shared_ptr<MeshNode> floor = make_shared<MeshNode>(PrimitiveType::Box);
				floor->setParent(room);
				floor->setColor(ofColor::black);
				floor->setScale(1.05f, 0.05f, 0.95f);
				floor->move(0.0f, -50.f, 0.0);

				shared_ptr<MeshNode> ceiling = make_shared<MeshNode>(PrimitiveType::Box);
				ceiling->setParent(room);
				ceiling->setColor(ofColor::black);
				ceiling->setScale(1.05f, 0.05f, 0.95f);
				ceiling->move(0.0f, 50.f, 0.0);
			}
		}

		return house;
	}
};