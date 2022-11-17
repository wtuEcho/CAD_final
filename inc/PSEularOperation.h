#pragma once

#include "PSCurve.h"
#include "PSEdge.h"
#include "PSFace.h"
#include "PSHalfEdge.h"
#include "PSLoop.h"
#include "PSSoild.h"
#include "PSVertex.h"

void mvfs(Vertex **v, Face **f, Solid **s, float point[3]);

void mev(Edge **ed, Vertex **ve2, Loop *lp, Vertex *v1, float point[3]);

void mef(Edge **edg, Face **f2, Vertex *v1, Vertex *v2, Loop *lp1);

void kemr(Loop **newlp, Vertex *v1, Vertex *v2, Loop *lp);

void kfmrh(Face *f1, Face *f2);

