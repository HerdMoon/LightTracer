#include "stdafx.h"
#include "BRTF.h"
#include <cmath>
#include "constant.h"

bool brtf::tir(ShadeRec & sr)                                              //全反射率判断
{
	Vector3D l_out(-sr.ray.d);
	double nodotl_out = sr.normal * l_out;
	double t_eta = eta;

	if (nodotl_out < 0.0)
	{
		t_eta = 1.0/ t_eta;                                               //反向判断全反射
	}
	if (1.0 - (1.0 - nodotl_out * nodotl_out) / (t_eta * t_eta) < 0.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

RGBColor brtf::sample_f(ShadeRec &sr,Vector3D& l_out,Vector3D& l_thr)
{
	Normal n(sr.normal);
	double nodotl_out = n * l_out;
	double t_eta = eta;

	if (nodotl_out <0.0)
	{
		nodotl_out =  - nodotl_out;
		n = -n;
		t_eta = 1.0/t_eta;
	}


	double t = (1.0 - (1.0 - nodotl_out * nodotl_out) / (t_eta * t_eta) < 0.0);
	double tt = sqrt(t);
	l_thr = -l_out / t_eta - (tt - t /t_eta) *n;
	return (kt / (t_eta * t_eta) * white /fabs(sr.normal * l_thr));
}