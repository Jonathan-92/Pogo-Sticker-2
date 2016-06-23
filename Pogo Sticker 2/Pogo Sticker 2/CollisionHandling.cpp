#include "CollisionHandling.h"

namespace gameEngine {

	CollisionHandling::CollisionHandling()
	{
	}

	CollisionHandling::~CollisionHandling()
	{
	}

	bool CollisionHandling::rectanglesOverlaps(Rect* myRect, Rect* other)
	{
		int left = myRect->x;					// left side of the rect
		int other_left = other->x;				// other rect's left side
		int right = myRect->x + myRect->w;				// etc...
		int other_right = other->x + other->w;
		int top = myRect->y;
		int other_top = other->y;
		int bottom = myRect->y + myRect->h;
		int other_bottom = other->y + other->h;

		if (bottom < other_top) return false;
		if (top > other_bottom) return false;

		if (right < other_left) return false;
		if (left > other_right) return false;

		return true;
	}

	bool line_intersect2(Pointbase* v1, Pointbase* v2, Pointbase* v3, Pointbase* v4)
	{
		float d = (v4 - v3)*(v2 - v1) - (v4 - v3)*(v2 - v1);
		float u = (v4 - v3)*(v1 - v3) - (v4 - v3)*(v1 - v3);
		float v = (v2 - v1)*(v1 - v3) - (v2 - v1)*(v1 - v3);
		if (d < 0)
		{
			u, v, d = -u, -v, -d;
		}
		return (0 <= u <= d) && (0 <= v <= d);
	}

	unsigned cross(vector<unsigned> v1, vector<unsigned> v2)
	{
		return v1[0] * v2[1] - v1[1] * v2[0];
	}

	bool point_in_triangle2(Pointbase* A, Pointbase* B, Pointbase* C, Pointbase* P)
	{ 
		vector<unsigned> v0(2);
		v0[0] = C->x - A->x;
		v0[1] = C->y - A->y;
		vector<unsigned> v1(2);
		v1[0] = B->x - A->x; 
		v1[1] = B->y - A->y;
		vector<unsigned> v2(2);
		v2[0] = P->x - A->x; 
		v2[1] = P->y - A->y;
		int u = cross(v2, v0);
		int v = cross(v1, v2);
		int d = cross(v1, v0);
		if (d < 0)
		{
			u, v, d = -u, -v, -d;
		}
		return u >= 0 && v >= 0 && (u + v) <= d;
	}

	bool CollisionHandling::trianglesOverlaps(Triangle* myTriangle, Triangle* other)
	{
		if (line_intersect2(myTriangle->getPoints()[0], myTriangle->getPoints()[1], other->getPoints()[0], other->getPoints()[0])) return true;
		//if (line_intersect2(myTriangle[0], myTriangle[1], other[0], other[2])) return true;
		//if (line_intersect2(myTriangle[0], myTriangle[1], other[1], other[2])) return true;
		//if (line_intersect2(myTriangle[0], myTriangle[2], other[0], other[1])) return true;
		//if (line_intersect2(myTriangle[0], myTriangle[2], other[0], other[2])) return true;
		//if (line_intersect2(myTriangle[0], myTriangle[2], other[1], other[2])) return true;
		//if (line_intersect2(myTriangle[1], myTriangle[2], other[0], other[1])) return true;
		//if (line_intersect2(myTriangle[1], myTriangle[2], other[0], other[2])) return true;
		//if (line_intersect2(myTriangle[1], myTriangle[2], other[1], other[2])) return true;

		bool inTri = true;
		
		inTri = inTri && point_in_triangle2(myTriangle->getPoints()[0], myTriangle->getPoints()[1], myTriangle->getPoints()[2], other->getPoints()[0]);
		//inTri = inTri && point_in_triangle2(myTriangle[0], myTriangle[1], myTriangle[2], other[1]);
		//inTri = inTri && point_in_triangle2(myTriangle[0], myTriangle[1], myTriangle[2], other[2]);
		if (inTri == true) return true;
				
		inTri = true;
		inTri = inTri && point_in_triangle2(other->getPoints()[0], other->getPoints()[1], other->getPoints()[2], myTriangle->getPoints()[0]);
		//inTri = inTri && point_in_triangle2(other[0], other[1], other[2], myTriangle[1]);
		//inTri = inTri && point_in_triangle2(other[0], other[1], other[2], myTriangle[2]);
		
		if (inTri == true) return true;
				
		return false;
	}

	bool CollisionHandling::triangleRectangleOverlaps(Rect* rectangle, Triangle* triangle)
	{
		Pointbase* rectPoint1 = new Pointbase(rectangle->x, rectangle->y);
		Pointbase* rectPoint2 = new Pointbase(rectangle->x + rectangle->w, rectangle->y);
		Pointbase* rectPoint3 = new Pointbase(rectangle->x, rectangle->y + rectangle->h);
		Pointbase* rectPoint4 = new Pointbase(rectangle->x + rectangle->w, rectangle->y + rectangle->h);

		bool inTri = true;

		inTri = inTri && point_in_triangle2(triangle->getPoints()[0], triangle->getPoints()[1], triangle->getPoints()[2], rectPoint1);
		//inTri = inTri && point_in_triangle2(myTriangle[0], myTriangle[1], myTriangle[2], other[1]);
		//inTri = inTri && point_in_triangle2(myTriangle[0], myTriangle[1], myTriangle[2], other[2]);
		//inTri = inTri && point_in_triangle2(myTriangle[0], myTriangle[1], myTriangle[2], other[2]);
		if (inTri == true) return true;

		inTri = true;
		//inTri = inTri && point_in_triangle2(rectangle->at(0), rectangle->at(1), rectangle->at(2), triangle->at(0));
		//inTri = inTri && point_in_triangle2(other[0], other[1], other[2], myTriangle[1]);
		//inTri = inTri && point_in_triangle2(other[0], other[1], other[2], myTriangle[2]);

		if (inTri == true) return true;

		return false;
	}

	bool CollisionHandling::intersect(WorldObject myRect, WorldObject other)
	{
		//Check outer rectangle before inner triangles for optimisation reasons

		if (rectanglesOverlaps(myRect.boundaryRectangle, other.boundaryRectangle))
		{
			for (int i = 0; i < other.triangles().size(); ++i)
			{

			}
		}
		return true;
	}

	bool CollisionHandling::intersect(Hitbox* rectangle, WorldObject* other)
	{
		//Check outer rectangle before inner triangles for optimisation reasons
		auto triangles = other->triangles();

		if (rectanglesOverlaps(rectangle, other->boundaryRectangle))
		{
			for (auto triangleIterator = triangles.begin(); triangleIterator != triangles.end(); ++triangleIterator)
			{
				if(triangleRectangleOverlaps(rectangle, &triangleIterator._Ptr->_Myval))
				{
					return true;
				}
			}
		}
		return false;
	}
}
