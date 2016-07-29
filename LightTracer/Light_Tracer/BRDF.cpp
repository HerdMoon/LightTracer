#include "stdafx.h"
#include "BRDF.h"
#include "constant.h"
#include <cmath>
Lambert::Lambert():rho_l(0),rho_c(RGBColor(0,0,0)){}

RGBColor Lambert::f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const
{
	return rho_l * rho_c * inv_pi;
}

RGBColor Lambert::rho(const ShadeRec & sr,Vector3D & l_in) const
{
	return rho_l * rho_c;
}

void Lambert::set_c(RGBColor c)
{
	rho_c = c;
}

void Lambert::set_l(double l)
{
	rho_l = l;
}

GlossySpecular::GlossySpecular():exp(0),rho_c(RGBColor(0,0,0)){}

RGBColor GlossySpecular::f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const
{
	RGBColor L;
	Normal temp_n;

	double ndotl_in = sr.normal * l_in;

	Vector3D r(-l_in + 2.0 *sr.normal *ndotl_in);
	double rdotl_out = r*l_out;

	if (rdotl_out > 0.0)
		L = rho_c * pow(rdotl_out,exp);
	return L;
}





void GlossySpecular::set_c(RGBColor c)
{
	rho_c = c;
}

void GlossySpecular::set_e(double l)
{
	exp = l;
}

RGBColor GlossySpecular::rho(const ShadeRec & sr,Vector3D & l_in) const
{
	return 0;
}

MirrorSpecular::MirrorSpecular():rho_l(0),rho_c(RGBColor(1,1,1)){}

void MirrorSpecular::set_c(RGBColor c)
{
	rho_c = c;
}

void MirrorSpecular::set_l(double l)
{
	rho_l = l;
}

RGBColor MirrorSpecular::sample_f(const ShadeRec &sr,const Vector3D &l_out,Vector3D &l_in) const
{
	double ndotl_out = sr.normal * l_out;
	l_in = -l_out + 2.0 * sr.normal * ndotl_out;
	return (rho_l * rho_c / (sr.normal * l_in));
}

RGBColor MirrorSpecular::f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const
{
	return 0;
}

RGBColor MirrorSpecular::rho(const ShadeRec & sr,Vector3D & l_in) const
{
	return 0;
}

TX_Lambertian::TX_Lambertian():rho_l(0),rho_c(new chess){}

RGBColor TX_Lambertian::f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const
{
	return rho_l * (rho_c->get_color(sr)) * inv_pi;
}

RGBColor TX_Lambertian::rho(const ShadeRec & sr,Vector3D & l_in) const
{
	return rho_l * rho_c->get_color(sr);
}


void TX_Lambertian::set_l(double l)
{
	rho_l = l;
}