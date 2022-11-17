#pragma once
#include "PSVertex.h"

class Face
{
public:
	static int num;
	int id;
	Face *prevf,  *nextf;
	Solid *fsolid;
	Loop *floop;
	Face() :prevf(nullptr), nextf(nullptr), fsolid(nullptr), floop(nullptr) { id = num++; }

};



