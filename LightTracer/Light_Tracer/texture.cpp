#include "stdafx.h"
#include "texture.h"
#include "constant.h"
RGBColor texture::get_color(const ShadeRec sr)
{
	return RGBColor(0);
}

RGBColor chess::get_color(const ShadeRec sr)
{
	int len = 2;
	int a = 20;
	double rx,rz;
	double tx = sr.local_hit_point.x;
	double tz = sr.local_hit_point.z;
	if (tx<0) {tx = -tx;}
	if (tz<0) {tz = -tz;}
	rx = tx - (int (tx/(len+a))) * (len+a);
	rz = tz - (int (tz /(len+a))) * (len+a);
	if ((rx<=len) || (rz<=len))
	{
		return black;
	}
	else
	{
		return white;
	}

}