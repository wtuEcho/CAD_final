#pragma once
#include "PSVertex.h"

class Loop
{
public:
	Loop *prevl,  *nextl;
	Face *lface;
	HalfEdge *ledg;
	bool inner;
	Loop() :prevl(nullptr), nextl(nullptr), lface(nullptr), ledg(nullptr), inner(false) { };
};