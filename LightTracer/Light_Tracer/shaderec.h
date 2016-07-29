#ifndef SHADEREC_H_
#define SHADEREC_H_
#include "Point3D.h"
#include "Normal.h"
#include "utility.h"
#include "ray.h"

class world;
class material;

using namespace std;
class ShadeRec{
	public:
		bool hit_an_object;             //是否有打到对象
		Point3D hit_point;              //光线打到对象上的点
		Point3D local_hit_point;
		Normal normal;                  //竖直离开平面
		material * mat_ptr;
		Ray ray;                        //入射光线
		int depth;                      //迭代次数
		RGBColor color;                 //返回颜色
		world& w;                       //world引用
		ShadeRec(world& wr);
		ShadeRec(const ShadeRec & sr);
	//	ShadeRec & operator=(const ShadeRec& rhs);
};


#endif