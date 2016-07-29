#include "stdafx.h"
#include "shaderec.h"



using namespace std;



ShadeRec::ShadeRec(world &wr):hit_an_object(false),mat_ptr(NULL),local_hit_point(),normal(),color(),w(wr),depth(0),ray()
{}

ShadeRec::ShadeRec(const ShadeRec & sr):hit_an_object(sr.hit_an_object),local_hit_point(sr.local_hit_point),normal(sr.normal),color(sr.color),w(sr.w),ray(sr.ray),depth(sr.depth),mat_ptr(sr.mat_ptr),hit_point(sr.hit_point){}