#pragma once
#include "PSEularOperation.h"
#include <vector>

void sweep(Face *f, float direction[], std::vector<Vertex*>& new_v, Face *outter_face);