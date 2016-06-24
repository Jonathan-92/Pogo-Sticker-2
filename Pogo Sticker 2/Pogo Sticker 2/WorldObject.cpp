#include "WorldObject.h"
#include "GL\glut.h"
#include <stack>

using namespace gameEngine;

WorldObject::WorldObject() : Polygon()
{
	boundaryRectangle = new Rect();
}

extern double orient2d(double* pa, double* pb, double* pc);

void UpdateKey(BTreeNode<Linebase*, double>* node, double y)
{
	node->data()->setKeyValue(y);
}

void WorldObject::generateHitboxes()
{
	initialize();
	partition2Monotone();
	searchMonotones();
	auto it = Monopolys.begin();
	for (; it != Monopolys.end(); it++)
		triangulateMonotone(&it._Ptr->_Myval);
	Triangles.size();
}

void WorldObject::partition2Monotone()
{
	while (!PQueue.empty())
	{
		Pointbase vertex = PQueue.top();
		PQueue.pop();
		unsigned int id = vertex.id;

		switch (vertex.type)
		{
			case Helperbase::START:        handleStartVertex(id);       break;
			case Helperbase::END:          handleEndVertex(id);         break;
			case Helperbase::MERGE:        handleMergeVertex(id);       break;
			case Helperbase::SPLIT:        handleSplitVertex(id);       break;
			case Helperbase::REGULAR_UP:   handleRegularVertexUp(id);   break;
			case Helperbase::REGULAR_DOWN: handleRegularVertexDown(id); break;
		}
	}
}

double WorldObject::angleCosb(double *pa, double *pb, double *pc)
{
	double dxab = pa[0] - pb[0];
	double dyab = pa[1] - pb[1];

	double dxcb = pc[0] - pb[0];
	double dycb = pc[1] - pb[1];

	double dxab2 = dxab * dxab;
	double dyab2 = dyab * dyab;
	double dxcb2 = dxcb * dxcb;
	double dycb2 = dycb * dycb;
	double ab = dxab2 + dyab2;
	double cb = dxcb2 + dycb2;

	double cosb = dxab * dxcb + dyab * dycb;
	double denom = sqrt(ab * cb);

	cosb /= denom;

	return cosb;
}

unsigned int WorldObject::selectNextEdge(Linebase* edge)
{

	unsigned int eid = edge->endPoint(1)->id;
	set<unsigned int> edges = AdjEdgeMap[eid];
	assert(!edges.empty());

	unsigned int nexte = 0;
	if (edges.size() == 1)  nexte = *(edges.begin());
	else if (edges.size() > 1)
	{
		unsigned int nexte_ccw(0), nexte_cw(0);
		double max = -2.0, min = 2.0;

		set<unsigned int>::iterator it = edges.begin();
		for (; it != edges.end(); it++)
		{
			if (*it == edge->id()) continue;
			double A[2], B[2], C[2];
			A[0] = edge->endPoint(0)->x;        
			A[1] = edge->endPoint(0)->y;
			B[0] = edge->endPoint(1)->x;        
			B[1] = edge->endPoint(1)->y;

			if (edge->endPoint(1) != Edges[*it]->endPoint(0))
			{
				Edges[*it]->reverse();
			}
			C[0] = Edges[*it]->endPoint(1)->x; C[1] = Edges[*it]->endPoint(1)->y;

			double area = orient2d(A, B, C);
			double cosb = angleCosb(A, B, C);

			if (area > 0 && max < cosb)
			{
				nexte_ccw = *it; max = cosb;
			}
			else if (min > cosb)
			{
				nexte_cw = *it; min = cosb;
			}
		}

		nexte = (nexte_ccw != 0) ? nexte_ccw : nexte_cw;
	}

	return nexte;
}

void WorldObject::searchMonotones()
{
	int loop = 0;

	auto edges = Edges;

	while (edges.size() > Diagonals.size())
	{
		loop++;
		Monotonepolygon poly = Monotonepolygon();
		map<unsigned int, Linebase*>::iterator it = edges.begin();
		Pointbase* startp = startp = it->second->endPoint(0);
		Pointbase* endp = 0;
		Linebase* next = it->second;

		poly.addPoint(startp);

		for (;;)
		{
			endp = next->endPoint(1);
			if (next->type() != Helperbase::INSERT)
			{
				edges.erase(next->id());
				AdjEdgeMap[next->endPoint(0)->id].erase(next->id());
			}
			if (endp == startp) break;
			poly.addPoint(endp);

			unsigned int nexte = selectNextEdge(next);
			//assert( nexte > 0);
			next = edges[nexte];
			if (next->endPoint(0) != endp) next->reverse();
		}

		Monopolys.push_back(poly);
	}
}

void  WorldObject::triangulateMonotone(Monotonepolygon* mpoly)
{
	priority_queue<Pointbase> qvertex;
	auto points = mpoly->getPoints();
	vector<Pointbase*>::iterator it = points.begin(), itnext;
	for (; itnext = it, it != points.end(); it++)
	{
		itnext++;
		if (itnext == points.end()) itnext = points.begin();
		Pointbase point = *(*it);
		Pointbase pointnext = *(*it + 1);
		point.left = (point > pointnext) ? true : false;
		qvertex.push(point);
	}

	stack<Pointbase> spoint;
	for (int i = 0; i < 2; i++) { spoint.push(qvertex.top()); qvertex.pop(); }

	while (qvertex.size() > 1)
	{
		Pointbase topQueuePoint = qvertex.top();
		Pointbase topStackPoint = spoint.top();

		if (topQueuePoint.left != topStackPoint.left)
		{
			while (spoint.size() > 1)
			{
				Pointbase p1 = spoint.top();
				spoint.pop();
				Pointbase p2 = spoint.top();
				Triangle* v = new Triangle(points[topQueuePoint.id], points[p1.id], points[p2.id]);
				Triangles.push_back(v);

			}
			spoint.pop();
			spoint.push(topStackPoint);
			spoint.push(topQueuePoint);
		}
		else
		{
			while (spoint.size() > 1)
			{
				Pointbase stack1Point = spoint.top();
				spoint.pop();
				Pointbase stack2Point = spoint.top();
				spoint.push(stack1Point);
				double pa[2], pb[2], pc[2];
				pa[0] = topQueuePoint.x; pa[1] = topQueuePoint.y;
				pb[0] = stack2Point.x;   pb[1] = stack2Point.y;
				pc[0] = stack1Point.x;   pc[1] = stack1Point.y;

				double area = orient2d(pa, pb, pc);
				bool   left = stack1Point.left;
				if ((area > 0 && left) || (area < 0 && !left))
				{
					Triangle* v = new Triangle(points[topQueuePoint.id], points[stack2Point.id], points[stack1Point.id]);
					Triangles.push_back(v);
					spoint.pop();
				}
				else break;
			}

			spoint.push(topQueuePoint);

		}

		qvertex.pop();

	}

	Pointbase lastQueuePoint = qvertex.top();
	while (spoint.size() != 1)
	{
		Pointbase topPoint = spoint.top();
		spoint.pop();
		Pointbase top2Point = spoint.top();

		Triangle* v = new Triangle(points[lastQueuePoint.id], points[topPoint.id], points[top2Point.id]);
		Triangles.push_back(v);
	}
}

void WorldObject::addDiagonal(unsigned int i, unsigned int j)
{
	Helperbase::Type type = Helperbase::INSERT;
	Linebase* diag = new Linebase(points[i], points[j], type);
	Edges[diag->id()] = diag;

	AdjEdgeMap[i].insert(diag->id());
	AdjEdgeMap[j].insert(diag->id());

	Diagonals[diag->id()] = diag;
}

//----------------------------------------------------------------------------
//Handle start vertex
//----------------------------------------------------------------------------
void WorldObject::handleStartVertex(unsigned int i)
{
	double y = points[i]->y;
	EdgeBST.InOrder(UpdateKey, y);

	Edges[i]->setHelper(i);
	Edges[i]->setKeyValue(y);
	EdgeBST.Insert(Edges[i]);
}

//----------------------------------------------------------------------------
//Handle end vertex
//----------------------------------------------------------------------------
void WorldObject::handleEndVertex(unsigned int i)
{
	double y = points[i]->y;
	EdgeBST.InOrder(UpdateKey, y);

	unsigned int previ = prev(i);
	Linebase* edge = Edges[previ];
	unsigned int helper = Edges[previ]->helper();


	if (points[helper]->type == Helperbase::MERGE) addDiagonal(i, helper);
	EdgeBST.Delete(edge->keyValue());
}

//----------------------------------------------------------------------------
//Handle split vertex
//----------------------------------------------------------------------------
void WorldObject::handleSplitVertex(unsigned int i)
{
	double x = points[i]->x, y = points[i]->y;
	EdgeBST.InOrder(UpdateKey, y);

	BTreeNode<Linebase*, double>*  leftnode;
	EdgeBST.FindMaxSmallerThan(x, leftnode);
	Linebase* leftedge = leftnode->data();

	unsigned int helper = leftedge->helper();
	addDiagonal(i, helper);

	leftedge->setHelper(i);
	Edges[i]->setHelper(i);
	Edges[i]->setKeyValue(y);
	EdgeBST.Insert(Edges[i]);
}


//----------------------------------------------------------------------------
//Handle merge vertex
//----------------------------------------------------------------------------
void WorldObject::handleMergeVertex(unsigned int i)
{
	double x = points[i]->x, y = points[i]->y;
	EdgeBST.InOrder(UpdateKey, y);

	unsigned int previ = prev(i);
	unsigned int helper = Edges[previ]->helper();
	if (points[helper]->type == Helperbase::MERGE) addDiagonal(i, helper);
	EdgeBST.Delete(Edges[previ]->keyValue());
	
	BTreeNode<Linebase*, double>*  leftnode;
	EdgeBST.FindMaxSmallerThan(x, leftnode);
	Linebase* leftedge = leftnode->data();

	helper = leftedge->helper();
	if (points[helper]->type == Helperbase::MERGE) addDiagonal(i, helper);

	leftedge->setHelper(i);

}

//----------------------------------------------------------------------------
//Handle regular down vertex
//----------------------------------------------------------------------------
void WorldObject::handleRegularVertexDown(unsigned int i)
{
	double y = points[i]->y;
	EdgeBST.InOrder(UpdateKey, y);

	unsigned int previ = prev(i);
	unsigned int helper = Edges[previ]->helper();
	if (points[helper]->type == Helperbase::MERGE) addDiagonal(i, helper);

	EdgeBST.Delete(Edges[previ]->keyValue());
	Edges[i]->setHelper(i);
	Edges[i]->setKeyValue(y);
	EdgeBST.Insert(Edges[i]);
}


//----------------------------------------------------------------------------
////Handle regular up vertex
//----------------------------------------------------------------------------
void WorldObject::handleRegularVertexUp(unsigned int i)
{
	double x = points[i]->x;
	double y = points[i]->y;
	EdgeBST.InOrder(UpdateKey, y);

	BTreeNode<Linebase*, double>*  leftnode;
	EdgeBST.FindMaxSmallerThan(x, leftnode);

	Linebase* leftedge = leftnode->data();

	unsigned int helper = leftedge->helper();
	if (points[helper]->type == Helperbase::MERGE) addDiagonal(i, helper);
	leftedge->setHelper(i);
}

unsigned int WorldObject::prev(unsigned int i)
{
	unsigned int j(0), prevLoop(0), currentLoop(0);

	while (i > _nVertices[currentLoop])
	{
		prevLoop = currentLoop;	
		currentLoop++;
	}

	if (i == 0 || (i == _nVertices[prevLoop] + 1)) j = _nVertices[currentLoop] - 1;
	else if (i <= _nVertices[currentLoop]) j = i - 1;

	return j;
}

//----------------------------------------------------------------------------
//return the next point (or edge) id for a given ith point (or edge);
//----------------------------------------------------------------------------
unsigned int WorldObject::next(unsigned int i)
{
	unsigned int j(0), prevLoop(0), currentLoop(0);

	while (i > _nVertices[currentLoop])
	{
		prevLoop = currentLoop;
		currentLoop++;
	}

	if (i + 1 < _nVertices[currentLoop]) j = i + 1;
	else if (i == _nVertices[currentLoop])
	{
		if (currentLoop == 0) j = 1;
		else j = _nVertices[prevLoop] + 1;
	}

	return j;
}


//----------------------------------------------------------------------------
//rotate a polygon by angle theta, reference point (0,0), not used;
//----------------------------------------------------------------------------
void WorldObject::rotate(double theta)
{
	for (auto it = points.begin(); it != points.end(); it++)
		(*it)->rotate(theta);
}

void WorldObject::draw()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin( GL_QUADS ); 
	for (auto it = points.begin(); it != points.end(); it++)
	{
		glVertex2f((*it)->x, (*it)->y);
		glColor3f(1.0, 0.0, 0.0);
	}
	glColor3f(0.0, 1.0, 0.0);
	glEnd();
}

void WorldObject::ReadPoints(int numberOfPoints)
{
	unsigned int i = 1, first, last;
	double x, y, xmin = 100000, ymin = 100000, xmax = -999999, ymax = -999999;
	Helperbase::Type type;

	_ncontours = 0;
	_nVertices.push_back(numberOfPoints);

	for (;;)
	{
		if (_nVertices.size() == _ncontours) break;

		if (_nVertices[_ncontours] == 0) break;
		first = i - 1;
		last = first + _nVertices[_ncontours] - 1;
		for (unsigned int j = 0; j < _nVertices[_ncontours]; j++, i++)
		{
			x = 250+j*5;
			y = 350+j*5*i;
			type = Helperbase::INPUTS;

			Pointbase* point = new Pointbase(i - 1, x, y, type);
			if (x > xmax) xmax = x;
			if (x < xmin) xmin = x;
			if (y > ymax) ymax = y;
			if (y < ymin) ymin = y;
			//point->rotate(PI/2.0);
			points.push_back(point);
		}

		boundaryRectangle->setRect(xmin, ymin, xmax - xmin, ymax - ymin);

		_ncontours++;
	}

	int sid, eid;
	int num = 0;

	for (unsigned int j = 0; j<_ncontours; j++)
	{
		for (i = 0; i <= _nVertices[j] - 1; i++)
		{
			sid = num + i;
			eid = (i == _nVertices[j] - 1) ? num : num + i + 1;
			type = Helperbase::INPUTS;
			Linebase* line = new Linebase(points[sid], points[eid], type);
			Edges[line->l_id - 1] = line;
		}
		num += _nVertices[j];
	}

	int sum = 0;
	for (unsigned int i = 0; i<_ncontours; i++)
	{
		sum += _nVertices[i];
		_nVertices[i] = sum;
	}
}

//----------------------------------------------------------------------------
//polygon initialization;
//to find types of all polygon vertices;
//create a priority queue for all vertices;
//construct an edge set for each vertex (the set holds all edges starting from 
//the vertex, only for loop searching purpose). 
//----------------------------------------------------------------------------
void WorldObject::initialize()
{
	for (auto it = points.begin(); it != points.end(); it++)
	{
		int id = (*it)->id;
		int idp = prev(id);
		int idn = next(id);
		Pointbase p = *points[id], pnext = *points[idn], pprev = *points[idp];

		if (p > pnext && pprev > p)
			points[id]->type = Helperbase::REGULAR_DOWN;
		else if (p > pprev && pnext > p)
			points[id]->type = Helperbase::REGULAR_UP;
		else
		{
			double pa[2], pb[2], pc[2];

			pa[0] = points[idp]->x;
			pa[1] = points[idp]->y;

			pb[0] = points[id]->x;
			pb[1] = points[id]->y;

			pc[0] = points[idn]->x;
			pc[1] = points[idn]->y;

			double area = orient2d(pa, pb, pc);

			if (pprev > p && pnext > p) points[id]->type = (area >0) ? Helperbase::END : Helperbase::MERGE;
			if (pprev < p && pnext < p) points[id]->type = (area >0) ? Helperbase::START : Helperbase::SPLIT;

		}

		PQueue.push(*(*it));

		AdjEdgeMap[id].insert(id);

	}
}