#include "WorldObject.h"
#include "GL\glut.h"
#include <stack>

using namespace gameEngine;

WorldObject::WorldObject() : Polygon()
{

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
	Monopolys::iterator it = _mpolys.begin();
	for (; it != _mpolys.end(); it++)
		triangulateMonotone(*it);
	_triangles.size();
}

void WorldObject::partition2Monotone()
{
	while (!_qpoints.empty())
	{
		Pointbase vertex = _qpoints.top();
		_qpoints.pop();
		unsigned int id = vertex.id;

		switch (vertex.type)
		{
			case START:        handleStartVertex(id);       break;
			case END:          handleEndVertex(id);         break;
			case MERGE:        handleMergeVertex(id);       break;
			case SPLIT:        handleSplitVertex(id);       break;
			case REGULAR_UP:   handleRegularVertexUp(id);   break;
			case REGULAR_DOWN: handleRegularVertexDown(id); break;
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
	set<unsigned int> edges = _startAdjEdgeMap[eid];
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
			A[0] = edge->endPoint(0)->x;        A[1] = edge->endPoint(0)->y;
			B[0] = edge->endPoint(1)->x;        B[1] = edge->endPoint(1)->y;

			if (edge->endPoint(1) != _edges[*it]->endPoint(0)) _edges[*it]->reverse();
			C[0] = _edges[*it]->endPoint(1)->x; C[1] = _edges[*it]->endPoint(1)->y;

			double area = orient2d(A, B, C);
			double cosb = angleCosb(A, B, C);

			if (area > 0 && max < cosb) { nexte_ccw = *it; max = cosb; }
			else if (min > cosb) { nexte_cw = *it; min = cosb; }
		}

		nexte = (nexte_ccw != 0) ? nexte_ccw : nexte_cw;
	}

	return nexte;
}

void WorldObject::searchMonotones()
{
	int loop = 0;

	LineMap edges = _edges;

	while (edges.size() > _diagonals.size())
	{
		loop++;
		Monopoly poly;
		LineMap::iterator it = edges.begin();
		Pointbase* startp = startp = it->second->endPoint(0);
		Pointbase* endp = 0;
		Linebase*  next = it->second;

		poly.push_back(startp->id);

		for (;;)
		{
			endp = next->endPoint(1);
			if (next->type() != INSERT)
			{
				edges.erase(next->id());
				_startAdjEdgeMap[next->endPoint(0)->id].erase(next->id());
			}
			if (endp == startp) break;
			poly.push_back(endp->id);

			unsigned int nexte = selectNextEdge(next);
			//assert( nexte > 0);
			next = edges[nexte];
			if (next->endPoint(0) != endp) next->reverse();
		}

		_mpolys.push_back(poly);
	}
}

void  WorldObject::triangulateMonotone(Monopoly& mpoly)
{

	PQueue qvertex;
	Monopoly::iterator it = mpoly.begin(), itnext;
	for (; itnext = it, it != mpoly.end(); it++)
	{
		itnext++;
		if (itnext == mpoly.end()) itnext = mpoly.begin();
		Pointbase point = *points[*it], pointnext = *points[*itnext];
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
				Triangle v(3);
				v[0] = topQueuePoint.id;
				v[1] = p1.id;
				v[2] = p2.id;
				_triangles.push_back(v);

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
					Triangle v(3);
					v[0] = topQueuePoint.id;
					v[1] = stack2Point.id;
					v[2] = stack1Point.id;
					_triangles.push_back(v);
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

		Triangle v(3);
		v[0] = lastQueuePoint.id;
		v[1] = topPoint.id;
		v[2] = top2Point.id;
		_triangles.push_back(v);
	}
}

void WorldObject::addDiagonal(unsigned int i, unsigned int j)
{
	Type type = INSERT;
	Linebase* diag = new Linebase(points[i], points[j], type);
	_edges[diag->id()] = diag;

	_startAdjEdgeMap[i].insert(diag->id());
	_startAdjEdgeMap[j].insert(diag->id());

	_diagonals[diag->id()] = diag;
}

//----------------------------------------------------------------------------
//Handle start vertex
//----------------------------------------------------------------------------
void WorldObject::handleStartVertex(unsigned int i)
{
	double y = points[i]->y;
	_edgebst.InOrder(UpdateKey, y);

	_edges[i]->setHelper(i);
	_edges[i]->setKeyValue(y);
	_edgebst.Insert(_edges[i]);
}

//----------------------------------------------------------------------------
//Handle end vertex
//----------------------------------------------------------------------------
void WorldObject::handleEndVertex(unsigned int i)
{
	double y = points[i]->y;
	_edgebst.InOrder(UpdateKey, y);

	unsigned int previ = prev(i);
	Linebase* edge = _edges[previ];
	unsigned int helper = _edges[previ]->helper();


	if (points[helper]->type == MERGE) addDiagonal(i, helper);
	_edgebst.Delete(edge->keyValue());
}

//----------------------------------------------------------------------------
//Handle split vertex
//----------------------------------------------------------------------------
void WorldObject::handleSplitVertex(unsigned int i)
{
	double x = points[i]->x, y = points[i]->y;
	_edgebst.InOrder(UpdateKey, y);

	BTreeNode<Linebase*, double>*  leftnode;
	_edgebst.FindMaxSmallerThan(x, leftnode);
	Linebase* leftedge = leftnode->data();

	unsigned int helper = leftedge->helper();
	addDiagonal(i, helper);

	leftedge->setHelper(i);
	_edges[i]->setHelper(i);
	_edges[i]->setKeyValue(y);
	_edgebst.Insert(_edges[i]);
}


//----------------------------------------------------------------------------
//Handle merge vertex
//----------------------------------------------------------------------------
void WorldObject::handleMergeVertex(unsigned int i)
{
	double x = points[i]->x, y = points[i]->y;
	_edgebst.InOrder(UpdateKey, y);

	unsigned int previ = prev(i);
	unsigned int helper = _edges[previ]->helper();
	if (points[helper]->type == MERGE) addDiagonal(i, helper);
	_edgebst.Delete(_edges[previ]->keyValue());
	
	BTreeNode<Linebase*, double>*  leftnode;
	_edgebst.FindMaxSmallerThan(x, leftnode);
	Linebase* leftedge = leftnode->data();

	helper = leftedge->helper();
	if (points[helper]->type == MERGE) addDiagonal(i, helper);

	leftedge->setHelper(i);

}

//----------------------------------------------------------------------------
//Handle regular down vertex
//----------------------------------------------------------------------------
void WorldObject::handleRegularVertexDown(unsigned int i)
{
	double y = points[i]->y;
	_edgebst.InOrder(UpdateKey, y);

	unsigned int previ = prev(i);
	unsigned int helper = _edges[previ]->helper();
	if (points[helper]->type == MERGE) addDiagonal(i, helper);

	_edgebst.Delete(_edges[previ]->keyValue());
	_edges[i]->setHelper(i);
	_edges[i]->setKeyValue(y);
	_edgebst.Insert(_edges[i]);
}


//----------------------------------------------------------------------------
////Handle regular up vertex
//----------------------------------------------------------------------------
void WorldObject::handleRegularVertexUp(unsigned int i)
{
	double x = points[i]->x, y = points[i]->y;
	_edgebst.InOrder(UpdateKey, y);

	BTreeNode<Linebase*, double>*  leftnode;
	_edgebst.FindMaxSmallerThan(x, leftnode);

	Linebase* leftedge = leftnode->data();

	unsigned int helper = leftedge->helper();
	if (points[helper]->type == MERGE) addDiagonal(i, helper);
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

	if (i == 1 || (i == _nVertices[prevLoop] + 1)) j = _nVertices[currentLoop];
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

	if (i < _nVertices[currentLoop]) j = i + 1;
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
	PointbaseMap::iterator it = points.begin();
	for (; it != points.end(); it++)
		it->second->rotate(theta);
}

void WorldObject::draw()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin( GL_QUADS ); 
	PointbaseMap::iterator it = points.begin();
	for (; it != points.end(); it++)
	{
		glVertex2f(it->second->x, it->second->y);
		glColor3f(1.0, 0.0, 0.0);
	}
	glEnd();
}

void WorldObject::ReadPoints(int numberOfPoints)
{
	unsigned int i = 1, first, last;
	double x, y;
	Type type;

	_ncontours = 0;
	_nVertices.push_back(numberOfPoints);

	for (;;)
	{
		if (_nVertices.size() == _ncontours) break;

		if (_nVertices[_ncontours] == 0) break;
		first = i;
		last = first + _nVertices[_ncontours] - 1;
		for (unsigned int j = 0; j < _nVertices[_ncontours]; j++, i++)
		{
			x = 200+j*2;
			y = 200+j*2*i;
			type = INPUTS;

			Pointbase* point = new Pointbase(i, x, y, type);
			//if (x > _xmax) _xmax = x;
			//if (x < _xmin) _xmin = x;
			//if (y > _ymax) _ymax = y;
			//if (y < _ymin) _ymin = y;
			//point->rotate(PI/2.0);
			points[i] = point;
		}

		_ncontours++;
	}

	int sid, eid;
	int num = 0;

	for (unsigned int j = 0; j<_ncontours; j++)
	{
		for (i = 1; i <= _nVertices[j]; i++)
		{
			sid = num + i;
			eid = (i == _nVertices[j]) ? num + 1 : num + i + 1;
			type = INPUTS;
			Linebase* line = new Linebase(points[sid], points[eid], type);
			_edges[line->l_id] = line;
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
	PointbaseMap::iterator it = points.begin();
	for (; it != points.end(); it++)
	{
		int id = it->first;
		int idp = prev(id);
		int idn = next(id);
		Pointbase p = *points[id], pnext = *points[idn], pprev = *points[idp];

		if (p > pnext && pprev > p)
			points[id]->type = REGULAR_DOWN;
		else if (p > pprev && pnext > p)
			points[id]->type = REGULAR_UP;
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

			if (pprev > p && pnext > p) points[id]->type = (area >0) ? END : MERGE;
			if (pprev < p && pnext < p) points[id]->type = (area >0) ? START : SPLIT;

		}

		_qpoints.push(*(it->second));

		_startAdjEdgeMap[id].insert(id);

	}
}