#pragma once
#include "PSVertex.h"


class HalfEdge
{
public:
	HalfEdge *prev,*next;
	Loop *wloop;
	Edge *edg;
	Vertex *startv;//start vertex of halfedge
	HalfEdge() :prev(nullptr), next(nullptr), wloop(nullptr), edg(nullptr), startv(nullptr) { }
};