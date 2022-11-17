#pragma once
#include "PSVertex.h"

class Solid
{
public:
	Solid *prevs, *nexts;
	Face *sface;
	Edge *sedge;
	Solid() :prevs(nullptr), nexts(nullptr), sface(nullptr), sedge(nullptr) { }
};