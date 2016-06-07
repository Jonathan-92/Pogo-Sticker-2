#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include "Hitbox.h"
#include "Linebase.h"

namespace gameEngine {
	class WorldObject : public Polygon {
	public:
		virtual ~WorldObject()
		{
		}

		WorldObject();
		std::list<gameEngine::Hitbox*> hitboxes;

		void generateHitboxes();
		void partition2Monotone();
		void searchMonotones();
		void ReadPoints(int numberOfPoints);

		void draw();

		//return all triangles
		Triangles triangles() { return _triangles; }
		
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
		void    triangulateMonotone(Monopoly& mpoly);

		unsigned int            _ncontours;   //number of contours
		vector<unsigned int>    _nVertices;   //
		LineMap                 _edges;       //all edges 
		//double                  _xmin, _xmax, _ymin, _ymax; boundary box for polygon

		PQueue      _qpoints;                            //priority queue for event points
		EdgeBST     _edgebst;                            //edge binary searching tree (splaytree) 
		Monopolys   _mpolys;                             //all monotone polygon piece list;
		Triangles   _triangles;                          //all triangle list;
													 //data for monotone piece searching purpose;
		AdjEdgeMap  _startAdjEdgeMap;                    //all edges starting from given points (map)   
		LineMap     _diagonals;
	};
}

#endif