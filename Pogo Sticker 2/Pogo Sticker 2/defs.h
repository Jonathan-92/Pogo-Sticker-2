#pragma once
#ifndef DEFS_H
#define DEFS_H 

#include <math.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <set>

using namespace std;

#define sqr(t)  (t)*(t)

enum  Type { UNKNOWN, INPUTS, INSERT, START, END, MERGE, SPLIT, REGULAR_UP, REGULAR_DOWN };

class Pointbase;
class Linebase;

template <class T, class KeyType>      class    SplayTree;
typedef map<unsigned int, Pointbase*>           PointbaseMap;
typedef map<unsigned int, Linebase*>            LineMap;
typedef priority_queue<Pointbase>               PQueue;
typedef SplayTree<Linebase*, double>            EdgeBST;
typedef list<unsigned int>                      Monopoly;
typedef list<Monopoly>                          Monopolys;
typedef vector<Pointbase*>                    Triangle;
typedef list<Triangle>                          Triangles;
typedef map<unsigned int, set<unsigned int> >   AdjEdgeMap;
#endif

