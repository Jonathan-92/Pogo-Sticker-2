#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include "Hitbox.h"
#include "Linebase.h"
#include "Polygon.h"
#include "Monotonepolygon.h"
#include <map>
#include <list>
#include <queue>
#include <set>
#include "Triangle.h"

using namespace std;

namespace gameEngine {
	class WorldObject : public Polygon {
	public:
		virtual ~WorldObject()
		{
		}

		WorldObject();
		std::list<gameEngine::Hitbox*> hitboxes;

		map<unsigned int, Pointbase*> PointbaseMap;
		map<unsigned int, Linebase*> Edges;
		map<unsigned int, Linebase*> Diagonals;
		priority_queue<Pointbase> PQueue;
		SplayTree<Linebase*, double> EdgeBST;
		list<Monotonepolygon> Monopolys;
		list<gameEngine::Triangle*>  Triangles;
		map<unsigned int, set<unsigned int>> AdjEdgeMap;

		void generateHitboxes();
		void partition2Monotone();
		void searchMonotones();
		void ReadPoints(int numberOfPoints);

		void draw();

		//return all triangles
		list<gameEngine::Triangle*> triangles() { return Triangles; }
		
	private:

		void rotate(double theta);
		void initialize();

		//prev or next point/edge id for a given ith point/edge; 	
		unsigned int prev(unsigned int i);
		unsigned int next(unsigned int i);

		//handle event vertext according to vertex type;
		void handleStartVertex(unsigned int);
		void handleEndVertex(unsigned int);
		void handleSplitVertex(unsigned int);
		void handleMergeVertex(unsigned int);
		void handleRegularVertexUp(unsigned int);
		void handleRegularVertexDown(unsigned int);

		//add diagonal between two vertices;
		void addDiagonal(unsigned int i, unsigned int j);


		//angle ABC for three given points, for monotone polygon searching purpose;
		double angleCosb(double *A, double *B, double *C);
		//find the next edge, for monotone polygon searching purpose;
		unsigned int selectNextEdge(Linebase* edge);

		//triangulate a monotone polygon piece;                        
		void    triangulateMonotone(Monotonepolygon* mpoly);

		unsigned int            _ncontours;   //number of contours
		vector<unsigned int>    _nVertices;   //
		//double                  _xmin, _xmax, _ymin, _ymax; boundary box for polygon
	};
}

#endif