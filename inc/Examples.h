#pragma once
#include "PSEularOperation.h"
#include "PSSweep.h"
#include <GL/glut.h>
#include <map>


std::map<float, std::map<float, std::map<float, int>>> m;//将坐标映射为id
std::vector<double*> mem_point;//gl使用的点信息,会分配内存

void print_Solid(Solid *s);
void print_Loop(Face* newf);

#define DRAW_EXAMPLE 1
Solid *Example1();
Solid *Example2();
Solid *Example3();


// 每当你添加新点，请使用该ADD_VERTEX去构建映射和用于渲染的点
#define ADD_VERTEX(point)\
{\
	m[point[0]][point[1]][point[2]] = mem_point.size();\
	double *_tmp_p = new double[6]{ point[0],point[1],point[2],\
	color[c_s % color_num][0],color[c_s % color_num][1], color[(c_s++) % color_num][2] };\
	mem_point.push_back(_tmp_p); \
	int _id = mem_point.size()-1;\
	printf("point:%2d\t  pos: %4.1f, %4.1f, %4.1f, \tcolor: %2.1f, %2.1f, %2.1f \n",_id,point[0],point[1],point[2], mem_point[_id][3], mem_point[_id][4], mem_point[_id][5] );\
}\

//颜色信息
const int color_num = 9;
int c_s = 0;
GLdouble color[color_num][3] = { {1.0, 0.0, 0.0},{0.0, 1.0, 0.0},{0.0, 0.0, 1.0},
								 {1.0, 1.0, 0.0},{1.0, 0.0, 1.0},{0.0, 1.0, 1.0},
								 {0.5, 0.5, 1.0},{0.5, 1.0, 0.5},{1.0, 0.5, 0.5} };

extern int print_time = 0;

void print_Solid(Solid *s);
void print_Loop(Face *newf);

Solid *Example1() {
	// 打孔长方体
	GLdouble quad2[8][3] = { {-2,3,0}, {-2,0,0}, {2,0,0}, { 2,3,0},
						 {-1,2,0}, {-1,1,0}, {1,1,0}, { 1,2,0} };

	float point[16][3] = {
		{-2,1.5,0	  },	{ -2,-1.5,0  },		{ 2,-1.5,0   },		{ 2,1.5,0   },
		{ -1,0.5,0  },		{ -1,-0.5,0  },		{ 1,-0.5,0   },		{ 1,0.5,0   },
		{-2,1.5,1	  },	{ -2,-1.5,1  },		{ 2,-1.5,1   },		{ 2,1.5,1   },
		{ -1,0.5,1  },		{ -1,-0.5,1  },		{ 1,-0.5,1   },		{ 1,0.5,1   }
	};
	
	for (int i = 0; i < 16; i++) {
		ADD_VERTEX(point[i])
	}
	

	Solid *s = nullptr;
	Face *f[12];
	Edge *e;
	Vertex *v[16];


	// 构造一个方形
	mvfs(&v[0], &f[0], &s, point[0]);
	mev(&e, &v[1], (s->sface->floop), v[0], point[1]);
	mev(&e, &v[2], (s->sface->floop), v[1], point[2]);
	mev(&e, &v[3], (s->sface->floop), v[2], point[3]);
	mef(&e, &f[1], v[3], v[0], (f[0]->floop));


	// 构造长方体
	mev(&e, &v[8], f[1]->floop, v[0], point[8]);
	mev(&e, &v[11], f[1]->floop, v[8], point[11]);
	mef(&e, &f[2], v[11], v[3], (f[1]->floop));

	mev(&e, &v[10], f[1]->floop, v[11], point[10]);
	mef(&e, &f[3], v[10], v[2], f[1]->floop);

	mev(&e, &v[9], f[1]->floop, v[10], point[9]);
	mef(&e, &f[4], v[9], v[1], f[1]->floop);
	mef(&e, &f[5], v[9], v[8], f[1]->floop);

	//构造环
	mev(&e, &v[4], f[0]->floop, v[0], point[4]);
	mev(&e, &v[7], f[0]->floop, v[4], point[7]);
	mev(&e, &v[6], f[0]->floop, v[7], point[6]);
	mev(&e, &v[5], f[0]->floop, v[6], point[5]);
	mef(&e, &f[6], v[5], v[4], f[0]->floop);

	Loop *lp_tmp;

	kemr(&lp_tmp, v[4], v[0], f[0]->floop);

	// 构造空心
	mev(&e, &v[12], f[6]->floop, v[4], point[12]);
	mev(&e, &v[13], f[6]->floop, v[5], point[13]);
	mev(&e, &v[14], f[6]->floop, v[6], point[14]);
	mev(&e, &v[15], f[6]->floop, v[7], point[15]);


	mef(&e, &f[7], v[12], v[13], f[6]->floop);
	mef(&e, &f[8], v[13], v[14], f[6]->floop);
	mef(&e, &f[9], v[14], v[15], f[6]->floop);
	mef(&e, &f[10], v[15], v[12], f[6]->floop);

	kfmrh(f[1], f[6]);

	return s;

}

Solid *Example2() {

	float point[8][3] = {
		{-2,1.5,0	  },	{ -2,-1.5,0  },		{ 2,-1.5,0   },		{ 2,1.5,0   },
		{ -1,0.5,0  },		{ -1,-0.5,0  },		{ 1,-0.5,0   },		{ 1,0.5,0   }
	};
	for (int i = 0; i < 8;i++) {
		ADD_VERTEX(point[i])
	}
	Face *f[3];
	Edge *e;
	Vertex *v[8];
	Solid *s = nullptr;
	// 构造一个方形
	mvfs(&v[0], &f[0], &s, point[0]);
	mev(&e, &v[1], (s->sface->floop), v[0], point[1]);
	mev(&e, &v[2], (s->sface->floop), v[1], point[2]);
	mev(&e, &v[3], (s->sface->floop), v[2], point[3]);
	mef(&e, &f[1], v[3], v[0], (f[0]->floop));

	//构造环
	mev(&e, &v[4], f[0]->floop, v[0], point[4]);
	mev(&e, &v[7], f[0]->floop, v[4], point[7]);
	mev(&e, &v[6], f[0]->floop, v[7], point[6]);
	mev(&e, &v[5], f[0]->floop, v[6], point[5]);
	mef(&e, &f[2], v[5], v[4], f[0]->floop);

	Loop *lp_tmp;

	kemr(&lp_tmp, v[4], v[0], f[0]->floop);

	std::vector<Vertex*> new_v;
	float direction[3] = { 1,1,-2 };
	sweep(s->sface,direction,new_v,f[1]);
	for (int i = 0; i < new_v.size(); i++) {
		float tmp_point[3] = { new_v[i]->x,new_v[i]->y, new_v[i]->z };
		ADD_VERTEX(tmp_point)
	}

	print_Solid(s);


	return s;
}

Solid *Example3() {
	Solid *s = nullptr;
	Face *f = nullptr,*tmp_f = nullptr;
	Edge *e = nullptr;
	Loop *lp = nullptr;
	Vertex *v[100];
	int v_idx;
	// c 只有外环
	float point_c[8][3] = {
	{ -2,1.5,-2	  },		{ -4,1.5,-2  },		{ -4,-1.5,-2},	{ -2,-1.5,-2   },
	{ -2,-1.2,-2  },		{ -3.7,-1.2,-2},	{ -3.7,1.2,-2},	{ -2,1.2,-2  }
	};
	v_idx = mem_point.size();
	for (int i = 0; i < 8; i++) {
		ADD_VERTEX(point_c[i])
	}
	
	mvfs(&v[v_idx + 0], &f, &s, point_c[0]);
	for (int i = 1; i < 8; i++) {
		mev(&e, &v[v_idx+i], s->sface->floop, v[v_idx + i - 1], point_c[i]);
	}
	mef(&e, &f,v[v_idx+7], v[v_idx+0],f->floop);
	

	// a 前8为外环，后4位内环
	float point_a[12][3] = {
		{1,1.5,-2.0},		{-1,1.5,-2.0},		{-1,-1.5,-2.0},	{-0.7,-1.5,-2.0},
		{-0.7,-0.15,-2.0},	{0.7,-0.15,-2.0},	{0.7,-1.5,-2.0},	{1,-1.5,-2.0},
		{0.7,1.2,-2.0},		{-0.7,1.2,-2.0},	{-0.7,0.15,-2.0},	{0.7,0.15,-2.0}
	};
	v_idx = mem_point.size();
	for (int i = 0; i < 12; i++) {
		ADD_VERTEX(point_a[i])
	}
	mvfs(&v[v_idx + 0], &f, &s, point_a[0]);
	for (int i = 1; i < 8; i++) {
		mev(&e, &v[v_idx + i], s->sface->floop, v[v_idx + i - 1], point_a[i]);
	}
	mef(&e, &tmp_f, v[v_idx + 7], v[v_idx + 0], f->floop);
	// 构造a的内环
	mev(&e, &v[v_idx + 8], s->sface->floop, v[v_idx + 0], point_a[8]);
	mev(&e, &v[v_idx +11], s->sface->floop, v[v_idx + 8], point_a[11]);
	mev(&e, &v[v_idx +10], s->sface->floop, v[v_idx +11], point_a[10]);
	mev(&e, &v[v_idx + 9], s->sface->floop, v[v_idx +10], point_a[9]);
	mef(&e, &tmp_f, v[v_idx + 9], v[v_idx + 8], f->floop);
	kemr(&lp, v[v_idx + 8], v[v_idx + 0], f->floop);


	//d 前5为外环，后5为内环
	float point_d[10][3] = {
		{4,1.5,-2.0},		{2,1.5,-2.0},		{2,-1.5,-2.0},		{2.6,-1.5,-2.0},		{4,-0.9,-2.0},
		{3.7,1.2,-2.0},		{2.3,1.2,-2.0},		{2.3,-1.2,-2.0} ,	{2.6,-1.2,-2.0},		{3.7,-0.6,-2.0},
	};
	v_idx = mem_point.size();
	for (int i = 0; i < 10; i++) {
		ADD_VERTEX(point_d[i])
	}
	mvfs(&v[v_idx + 0], &f, &s, point_d[0]);
	for (int i = 1; i < 5; i++) {
		mev(&e, &v[v_idx + i], s->sface->floop, v[v_idx + i - 1], point_d[i]);
	}
	mef(&e, &tmp_f, v[v_idx + 4], v[v_idx + 0], f->floop);
	// 构造a的内环
	mev(&e, &v[v_idx + 5], s->sface->floop, v[v_idx + 0], point_d[5]);
	mev(&e, &v[v_idx + 9], s->sface->floop, v[v_idx + 5], point_d[9]);
	mev(&e, &v[v_idx + 8], s->sface->floop, v[v_idx + 9], point_d[8]);
	mev(&e, &v[v_idx + 7], s->sface->floop, v[v_idx + 8], point_d[7]);
	mev(&e, &v[v_idx + 6], s->sface->floop, v[v_idx + 7], point_d[6]);
	mef(&e, &tmp_f, v[v_idx + 6], v[v_idx + 5], f->floop);
	kemr(&lp, v[v_idx + 5], v[v_idx + 0], f->floop);


	// 外框
	float point_f[8][3] = {
	{5.5,3.6,-2.0},	{-5.5,3.6,-2.0},		{-5.5,-2.5,-2.0},		{5.5,-2.5,-2.0},
	{5,2,-2.0},	{-5,2,-2.0},	{-5,-2,-2.0} ,	{5,-2,-2.0}
	};
	v_idx = mem_point.size();
	for (int i = 0; i < 8; i++) {
		ADD_VERTEX(point_f[i])
	}
	mvfs(&v[v_idx + 0], &f, &s, point_f[0]);
	for (int i = 1; i < 4; i++) {
		mev(&e, &v[v_idx + i], s->sface->floop, v[v_idx + i - 1], point_f[i]);
	}
	mef(&e, &tmp_f, v[v_idx + 3], v[v_idx + 0], f->floop);
	// 构造a的内环
	mev(&e, &v[v_idx + 4], s->sface->floop, v[v_idx + 0], point_f[4]);
	mev(&e, &v[v_idx + 7], s->sface->floop, v[v_idx + 4], point_f[7]);
	mev(&e, &v[v_idx + 6], s->sface->floop, v[v_idx + 7], point_f[6]);
	mev(&e, &v[v_idx + 5], s->sface->floop, v[v_idx + 6], point_f[5]);
	mef(&e, &tmp_f, v[v_idx + 5], v[v_idx + 4], f->floop);
	kemr(&lp, v[v_idx + 4], v[v_idx + 0], f->floop);
	point_f[4][0] = -4.05, point_f[4][1] = 3.3;
	point_f[5][0] = -5.05, point_f[5][1] = 3.3;
	point_f[6][0] = -5.05, point_f[6][1] = 2.3;
	point_f[7][0] = -4.05, point_f[7][1] = 2.3;
	for (int i = 0; i < 8; i++) {
		for (int j = 4; j < 8; j++) {
			ADD_VERTEX(point_f[j])
		}
		mev(&e, &v[v_idx + 4], s->sface->floop, v[v_idx + 0], point_f[4]);
		mev(&e, &v[v_idx + 7], s->sface->floop, v[v_idx + 4], point_f[7]);
		mev(&e, &v[v_idx + 6], s->sface->floop, v[v_idx + 7], point_f[6]);
		mev(&e, &v[v_idx + 5], s->sface->floop, v[v_idx + 6], point_f[5]);
		mef(&e, &tmp_f, v[v_idx + 5], v[v_idx + 4], f->floop);
		kemr(&lp, v[v_idx + 4], v[v_idx + 0], f->floop);
		for (int j = 4; j < 8; j++) {
			point_f[j][0] += 1.3;
		}
	}


	std::vector<Vertex*> new_v;
	float direction[3] = { 0.5,0.5,-1 };
	//前移到第一个face
	for (s; s->prevs != nullptr; s = s->prevs);

	printf("-----------------------follows the faces wait for sweep--------------------");
	for (Solid *tmp_s = s; tmp_s != nullptr; tmp_s = tmp_s->nexts) {
		print_Solid(s);
	}

	for (s; s->nexts != nullptr; s = s->nexts) {
		sweep(s->sface, direction, new_v, s->sface->nextf);
	}
	sweep(s->sface, direction, new_v, s->sface->nextf);

	for (int i = 0; i < new_v.size(); i++) {
		float tmp_point[3] = { new_v[i]->x,new_v[i]->y, new_v[i]->z };
		ADD_VERTEX(tmp_point)
	}

	for (s; s->prevs != nullptr; s = s->prevs);
	return s;
}




void print_Solid(Solid *s) {
	if (s == nullptr) {
		printf("no solid!");
		return;
	}
	printf("\n-----------------------------print time : %d-----------------------------------\n", print_time++);
	for (Face *f = s->sface; f != nullptr; f = f->nextf) {
		int lp_count = 0;
		if (f->floop == nullptr)
			printf("face id :%d has no loop\n", f->id);
		for (Loop *lp = f->floop; lp != nullptr; lp = lp->nextl) {
			printf("face id :%d ,the %d lp: ", f->id, lp_count);
			HalfEdge *edg = lp->ledg;
			Vertex *start = edg->startv;
			//printf("{%2.1f,%2.1f,%2.1f}, ", edg->startv->x,edg->startv->y,edg->startv->z);
			printf("%d - ", m[edg->startv->x][edg->startv->y][edg->startv->z]);
			edg = edg->next;
			while (edg->startv != start) {
				printf("%d - ", m[edg->startv->x][edg->startv->y][edg->startv->z]);
				edg = edg->next;
			}
			printf("%d", m[edg->startv->x][edg->startv->y][edg->startv->z]);
			if (lp->inner) {
				printf("   inner loop!\n");
			}
			else {
				printf("\n");
			}
			lp_count++;
		}
		printf("\n");
	}
}


void print_Loop(Face *newf) {
	//print loop;
	{
		printf("print time : %d ,face_id %d , the lp: ", print_time++, newf->id);
		Loop *_lp = newf->floop;
		HalfEdge *edg = _lp->ledg;
		Vertex *start = edg->startv;
		printf("{%2.0f,%2.0f,%2.0f}, ", edg->startv->x, edg->startv->y, edg->startv->z);
		edg = edg->next;
		while (edg->startv != start) {
			printf("{%2.0f,%2.0f,%2.0f}, ", edg->startv->x, edg->startv->y, edg->startv->z);
			edg = edg->next;
		}
		printf("{%2.0f,%2.0f,%2.0f}\t", edg->startv->x, edg->startv->y, edg->startv->z);
		if (_lp->inner) {
			printf("   inner loop!\n");
		}
		else {
			printf("\n");
		}
	}
}