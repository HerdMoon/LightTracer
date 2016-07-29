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
		bool hit_an_object;             //�Ƿ��д򵽶���
		Point3D hit_point;              //���ߴ򵽶����ϵĵ�
		Point3D local_hit_point;
		Normal normal;                  //��ֱ�뿪ƽ��
		material * mat_ptr;
		Ray ray;                        //�������
		int depth;                      //��������
		RGBColor color;                 //������ɫ
		world& w;                       //world����
		ShadeRec(world& wr);
		ShadeRec(const ShadeRec & sr);
	//	ShadeRec & operator=(const ShadeRec& rhs);
};


#endif