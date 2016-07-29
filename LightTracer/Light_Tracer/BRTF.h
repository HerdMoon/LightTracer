#ifndef BRTF_H_
#define BRTF_H_

#include "shaderec.h"
#include "Vector3D.h"
class brtf{
public:
	RGBColor sample_f(ShadeRec &sr,Vector3D& l_out,Vector3D& l_thr);        //sample_f描述的是投射情况
	bool tir(ShadeRec & sr);                                              //全反射率判断
	RGBColor kt;       //各色系数折射过程能量损失
	double eta;        //折射率

};



#endif