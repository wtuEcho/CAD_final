#pragma once
#include "PSVertex.h"

class Edge
{
public:
	HalfEdge *he1,  *he2;
	Edge() :he1(nullptr), he2(nullptr) { }
};
