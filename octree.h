

#pragma once

#include "Vector.h"
#include <vector>
#include "BoundingSphere.h"

class Object {
public:
	Vector center;
	float radius;
	Object(Vector center, float radius);
};


//Box representing the space of the world that will be devise un smaller box if needs
class BoundingBox {

public:
	Vector m_min, m_max;

	BoundingBox() : m_min(Vector()), m_max(Vector()) {}
	BoundingBox(const Vector& min, const Vector& max);

	void draw();

	bool IsContainingBS(BoundingSphere* sphere);
};


//node of the octree
class OctreeNode
{
public:

	OctreeNode(const BoundingBox& bounds);

	//Insert an object in the node
	void Insert(BoundingSphere* sphere);

	//display all informations of the OctreeNode and its childs
	void Display(int depth = 0);

	void draw();

	//box representing this node
	BoundingBox m_bounds;
	//objects contain in this node
	std::vector<BoundingSphere*> m_sphere;
	//childs of this node
	OctreeNode* children[8];

private:

	static const int MAX_OBJECTS = 2;

	void Distribute(BoundingSphere* sphere);

	void Split();
};
