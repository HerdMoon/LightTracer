#ifndef BRTF_H_
#define BRTF_H_

#include "shaderec.h"
#include "Vector3D.h"
class brtf{
public:
	RGBColor sample_f(ShadeRec &sr,Vector3D& l_out,Vector3D& l_thr);        //sample_f��������Ͷ�����
	bool tir(ShadeRec & sr);                                              //ȫ�������ж�
	RGBColor kt;       //��ɫϵ���������������ʧ
	double eta;        //������

};



#endif