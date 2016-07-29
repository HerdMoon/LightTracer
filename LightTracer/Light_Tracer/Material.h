#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "utility.h"
#include "shaderec.h"
#include "BRDF.h"
#include "BRTF.h"
//每个材料由漫反射系数(总体系数rho_l,各色系数rho_c)决定，即rho = rho_l * rho_c


class material {
	public:
		virtual RGBColor shade(ShadeRec& sr);

};

class Matte:public material{
	public:
		Matte();
		void set_rho_bg_light(const double r);           //设置背景光的漫反射系数
		void set_rho_df_light(const double r);                //设置漫反射光的漫反射系数
		void set_c_light(const RGBColor c);
		virtual RGBColor shade(ShadeRec& sr);
	private:
		Lambert * bg_light_brdf;
	    Lambert * df_light_brdf;

};

class Phong:public material{
	public:
		Phong();
		void set_rho_bg_light(const double r);
		void set_rho_df_light(const double r);
		void set_c_light(const RGBColor c);
		void set_ks_sp_light(const RGBColor k);
		void set_exp_sp_light(const double e);
		virtual RGBColor shade(ShadeRec &sr);
	 
	protected:
	    Lambert * bg_light_brdf;
		Lambert * df_light_brdf;
		GlossySpecular * sp_light_brdf;
};

class Mirror_mat:public Phong{                       //继承自Phong模型
	public:
		Mirror_mat();
		void set_rl_rf_light(const double l);
		void set_rc_rf_light(RGBColor c);
		virtual RGBColor shade(ShadeRec &sr);
	private:
		MirrorSpecular * rf_light_brdf;
};

class TX_Matte:public material {
	public:
		TX_Matte();
		void set_rho_bg_light(const double r);           //设置背景光的漫反射系数
		void set_rho_df_light(const double r);                //设置漫反射光的漫反射系数
		virtual RGBColor shade(ShadeRec& sr);
	private:
		TX_Lambertian * bg_light_brdf;
	    TX_Lambertian * df_light_brdf;
};

class Trans_Mat:public Phong {
	public:
		Trans_Mat();
		void set_rl_eta_light(const double l);
		void set_rc_kt_light(RGBColor c);
		void set_rl_rf_light(const double l);
		void set_rc_rf_light(RGBColor c);
		virtual RGBColor shade(ShadeRec &sr);
	private:
		MirrorSpecular * rf_light_brdf;
		brtf * tr_light_brtf;

};

#endif