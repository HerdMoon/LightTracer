#include "stdafx.h"
#include "light.h"
#include "constant.h"
#include "world.h"
light::light():shadow_exist(false){}
bg_light::bg_light():light(),l(background_light_lumi),color_bg(background_light_color){}
pt_light::pt_light():light(),l(background_light_lumi),color_pt(background_light_color),loc(Point3D(0)){}

Vector3D bg_light::get_dir(ShadeRec& sr) const
{
	return Vector3D(0);
}

RGBColor bg_light::get_lum(ShadeRec& sr) const
{
	return (l*color_bg);
}

void bg_light::set_lum(double r)
{
	l = r;
}

Vector3D pt_light::get_dir(ShadeRec& sr) const
{
	return ((loc-sr.local_hit_point).hat());
}

RGBColor pt_light::get_lum(ShadeRec& sr) const
{
	return (l*color_pt);
}


void pt_light::set_loc(double x,double y,double z)
{
	loc = Point3D(x,y,z);
}

void pt_light::set_lum(double r)
{
	l = r;
}

bool pt_light::get_sha()
{
	return shadow_exist;
}

void pt_light::set_sha(bool sha)
{
	shadow_exist = sha;
}

bool bg_light::get_sha()
{
	return shadow_exist;
}

void bg_light::set_sha(bool sha)
{
	shadow_exist = sha;
}

bool bg_light::shadow_check(const Ray&ray,const ShadeRec & sr) const
{
	return false;
}

bool pt_light::shadow_check(const Ray&ray,const ShadeRec & sr) const
{
	double t;
	int num_object = sr.w.object.size();
	float d = loc.distance(ray.o);

	for (int j=0;j<num_object;j++)
	{
		if (sr.w.object[j] ->shadow_hit(ray,t) && t<d)
			return (true);

	}
	return false;
}