#include "CollisionHandling.h"

namespace gameEngine {

	CollisionHandling::CollisionHandling()
	{
	}

	bool CollisionHandling::overlaps(Rect* myRect, Rect* other)
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

	bool line_intersect2(vector<unsigned> v1, vector<unsigned> v2, vector<unsigned> v3, vector<unsigned> v4)
	{
		float d = (v4[1] - v3[1])*(v2[0] - v1[0]) - (v4[0] - v3[0])*(v2[1] - v1[1]);
		float u = (v4[0] - v3[0])*(v1[1] - v3[1]) - (v4[1] - v3[1])*(v1[0] - v3[0]);
		float v = (v2[0] - v1[0])*(v1[1] - v3[1]) - (v2[1] - v1[1])*(v1[0] - v3[0]);
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

	bool point_in_triangle2(vector<unsigned> A, vector<unsigned> B, vector<unsigned> C, vector<unsigned> P)
	{
		vector<unsigned> v0;
		v0[0] = C[0] - A[0]; v0[1] = C[1] - A[1];
		vector<unsigned> v1;
		v1[0] = B[0] - A[0]; v1[1] = B[1] - A[1];
		vector<unsigned> v2;
		v2[0] = P[0] - A[0]; v2[1] = P[1] - A[1];
		int u = cross(v2, v0);
		int v = cross(v1, v2);
		int d = cross(v1, v0);
		if (d < 0)
		{
			u, v, d = -u, -v, -d;
		}
		return u >= 0 && v >= 0 && (u + v) <= d;
	}

	bool CollisionHandling::overlaps(Triangle* myTriangle, Triangle* other)
	{
		if (line_intersect2(myTriangle[0], myTriangle[1], other[0], other[1])) return true;
		if (line_intersect2(myTriangle[0], myTriangle[1], other[0], other[2])) return true;
		if (line_intersect2(myTriangle[0], myTriangle[1], other[1], other[2])) return true;
		if (line_intersect2(myTriangle[0], myTriangle[2], other[0], other[1])) return true;
		if (line_intersect2(myTriangle[0], myTriangle[2], other[0], other[2])) return true;
		if (line_intersect2(myTriangle[0], myTriangle[2], other[1], other[2])) return true;
		if (line_intersect2(myTriangle[1], myTriangle[2], other[0], other[1])) return true;
		if (line_intersect2(myTriangle[1], myTriangle[2], other[0], other[2])) return true;
		if (line_intersect2(myTriangle[1], myTriangle[2], other[1], other[2])) return true;

		bool inTri = true;
		
		inTri = inTri && point_in_triangle2(myTriangle[0], myTriangle[1], myTriangle[2], other[0]);
		inTri = inTri && point_in_triangle2(myTriangle[0], myTriangle[1], myTriangle[2], other[1]);
		inTri = inTri && point_in_triangle2(myTriangle[0], myTriangle[1], myTriangle[2], other[2]);
		if (inTri == true) return true;
				
		inTri = true;
		inTri = inTri && point_in_triangle2(other[0], other[1], other[2], myTriangle[0]);
		inTri = inTri && point_in_triangle2(other[0], other[1], other[2], myTriangle[1]);
		inTri = inTri && point_in_triangle2(other[0], other[1], other[2], myTriangle[2]);
		
		if (inTri == true) return true;
				
		return false;
	}

	bool CollisionHandling::intersect(WorldObject myRect, WorldObject other)
	{
		//Check outer rectangle before inner triangles for optimisation reasons

		if (overlaps(&myRect.rectangle, &other.rectangle))
		{
			for (int i = 0; i < other.triangles().size(); ++i)
			{

			}
		}
		return true;
	}

	void CollisionHandling::generateHitboxes(WorldObject worldObject)
	{
		worldObject.generateHitboxes();
	}
}
