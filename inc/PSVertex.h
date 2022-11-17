#pragma once
#include<vector>
class Solid;
class Face;
class Loop;
class Edge;
class HalfEdge;

class Vertex
{
public:
	float x, y, z;
	Vertex(float point[3]) :x(point[0]), y(point[1]), z(point[2]) { }
};
