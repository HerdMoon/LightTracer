#include "stdafx.h"
#include "Material.h"
#include "world.h"

RGBColor material::shade(ShadeRec& sr)
{
	return RGBColor(0.0);
}

Matte::Matte():bg_light_brdf(new Lambert),df_light_brdf(new Lambert){}

void Matte::set_rho_bg_light(const double r)
{
	bg_light_brdf->set_l(r);
}

void Matte::set_rho_df_light(const double r)
{
	df_light_brdf->set_l(r);
}

void Matte::set_c_light(const RGBColor c)
{
	bg_light_brdf->set_c(c);
	df_light_brdf->set_c(c);
}

RGBColor Matte::shade(ShadeRec & sr)
{
	Vector3D out_light = -sr.ray.d;            //入射光线方向
	out_light.normalize();
	RGBColor L = bg_light_brdf ->rho(sr,out_light) * (sr.w.env_light->get_lum(sr)); //背景项 = 材料吸收率* 背景光
	int n_light = sr.w.lights.size();

	for (int i=0;i<n_light;i++)
	{
		Vector3D in_light = sr.w.lights[i] ->get_dir(sr);       //入射光线方向(点光源出发点-击打点）
		in_light.normalize();
		double n_dot_in_light = sr.normal * in_light;
		if (n_dot_in_light > 0.0)
		{
			bool in_shadow = false;
			if (sr.w.lights[i]->get_sha())
			{
				Ray Shadow_Ray(sr.hit_point,in_light);
				in_shadow = sr.w.lights[i]->shadow_check(Shadow_Ray,sr);
			}
			if (!in_shadow)
			{
			L += df_light_brdf->f(sr,out_light,in_light) * sr.w.lights[i] ->get_lum(sr) * n_dot_in_light;
			}
		}
	}
	return L;

}

Phong::Phong():bg_light_brdf(new Lambert),df_light_brdf(new Lambert),sp_light_brdf(new GlossySpecular){}


void Phong::set_rho_bg_light(const double r)
{
	bg_light_brdf->set_l(r);
}

void Phong::set_rho_df_light(const double r)
{
	df_light_brdf->set_l(r);
}

void Phong::set_c_light(const RGBColor c)
{
	bg_light_brdf->set_c(c);
	df_light_brdf->set_c(c);
}

void Phong::set_exp_sp_light(const double e)
{
	sp_light_brdf ->set_e(e);
}

void Phong::set_ks_sp_light(const RGBColor k)
{
	sp_light_brdf ->set_c(k);
}

RGBColor Phong::shade(ShadeRec &sr)
{
	Vector3D out_light = -sr.ray.d;            //入射光线方向
	out_light.normalize();
	RGBColor L = bg_light_brdf ->rho(sr,out_light) * (sr.w.env_light->get_lum(sr)); //背景项 = 材料吸收率* 背景光
	int n_light = sr.w.lights.size();

	for (int i=0;i<n_light;i++)
	{
		Vector3D in_light = sr.w.lights[i] ->get_dir(sr);       //入射光线方向(点光源出发点-击打点）
		in_light.normalize();
		double n_dot_in_light = sr.normal * in_light;
		if (n_dot_in_light > 0.0)
		{
			bool in_shadow = false;
			if (sr.w.lights[i]->get_sha())
			{
				Ray Shadow_Ray(sr.hit_point,in_light);
				in_shadow = sr.w.lights[i]->shadow_check(Shadow_Ray,sr);
			}
			if (!in_shadow)
			 L += (df_light_brdf->f(sr,out_light,in_light)+sp_light_brdf ->f(sr,in_light,out_light))* sr.w.lights[i] ->get_lum(sr) * n_dot_in_light;
		}
	}
	return L;
}

Mirror_mat::Mirror_mat():Phong(){rf_light_brdf = new MirrorSpecular;}

void Mirror_mat::set_rl_rf_light(const double l)
{
	rf_light_brdf ->set_l(l);
}


void Mirror_mat::set_rc_rf_light(RGBColor c)
{
	rf_light_brdf ->set_c(c);
}

RGBColor Mirror_mat::shade(ShadeRec &sr)
{
	RGBColor L(Phong::shade(sr));          //先计算全局光照

	Vector3D l_out = -sr.ray.d;
	Vector3D l_in;
	RGBColor light_f = rf_light_brdf ->sample_f (sr,l_out,l_in);
	Ray rf_ray(sr.hit_point,l_in);
	L += light_f * sr.w.tracer_ptr ->trace_ray(rf_ray,sr.depth + 1) * (sr.normal *l_in);

	return L;

}

TX_Matte::TX_Matte():bg_light_brdf(new TX_Lambertian),df_light_brdf(new TX_Lambertian){}

void TX_Matte::set_rho_bg_light(const double r)
{
	bg_light_brdf->set_l(r);
}

void TX_Matte::set_rho_df_light(const double r)
{
	df_light_brdf->set_l(r);
}


RGBColor TX_Matte::shade(ShadeRec & sr)
{
	Vector3D out_light = -sr.ray.d;            //入射光线方向
	out_light.normalize();
	RGBColor L = bg_light_brdf ->rho(sr,out_light) * (sr.w.env_light->get_lum(sr)); //背景项 = 材料吸收率* 背景光
	int n_light = sr.w.lights.size();

	for (int i=0;i<n_light;i++)
	{
		Vector3D in_light = sr.w.lights[i] ->get_dir(sr);       //入射光线方向(点光源出发点-击打点）
		in_light.normalize();
		double n_dot_in_light = sr.normal * in_light;
		if (n_dot_in_light > 0.0)
		{
			bool in_shadow = false;
			if (sr.w.lights[i]->get_sha())
			{
				Ray Shadow_Ray(sr.hit_point,in_light);
				in_shadow = sr.w.lights[i]->shadow_check(Shadow_Ray,sr);
			}
			if (!in_shadow)
			{
			L += df_light_brdf->f(sr,out_light,in_light) * sr.w.lights[i] ->get_lum(sr) * n_dot_in_light;
			}
		}
	}
	return L;

}

Trans_Mat::Trans_Mat():Phong(){rf_light_brdf = new MirrorSpecular;tr_light_brtf = new brtf;}
void Trans_Mat::set_rl_eta_light(const double l)
{
	tr_light_brtf ->eta = l;
}

void Trans_Mat::set_rc_kt_light(RGBColor c)
{
	tr_light_brtf ->kt = c;
}
void Trans_Mat::set_rl_rf_light(const double l)
{
	rf_light_brdf ->set_l(l);
}
void Trans_Mat::set_rc_rf_light(RGBColor c)
{
	rf_light_brdf ->set_c(c);
}

RGBColor Trans_Mat::shade(ShadeRec & sr)
{
	RGBColor L(Phong::shade(sr));          //先计算全局光照

	Vector3D l_out = -sr.ray.d;
	Vector3D l_in;
	RGBColor light_f = rf_light_brdf ->sample_f (sr,l_out,l_in);
	Ray rf_ray(sr.hit_point,l_in);

	if (tr_light_brtf->tir(sr))
	{
		//set_rl_rf_light(1);
		L += light_f * sr.w.tracer_ptr ->trace_ray(rf_ray,sr.depth + 1);
	}
	else
	{
		Vector3D l_tr;
		RGBColor ft = tr_light_brtf->sample_f(sr,l_out,l_tr);
		Ray tr_ray(sr.hit_point,l_tr);

		L += light_f * sr.w.tracer_ptr ->trace_ray(rf_ray,sr.depth +1 ) *(sr.normal * l_in);
		L += ft * sr.w.tracer_ptr ->trace_ray(tr_ray,sr.depth+1) * (sr.normal * l_tr);
	}
	return L;

}