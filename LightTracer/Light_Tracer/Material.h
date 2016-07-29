#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "utility.h"
#include "shaderec.h"
#include "BRDF.h"
#include "BRTF.h"
//ÿ��������������ϵ��(����ϵ��rho_l,��ɫϵ��rho_c)��������rho = rho_l * rho_c


class material {
	public:
		virtual RGBColor shade(ShadeRec& sr);

};

class Matte:public material{
	public:
		Matte();
		void set_rho_bg_light(const double r);           //���ñ������������ϵ��
		void set_rho_df_light(const double r);                //������������������ϵ��
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

class Mirror_mat:public Phong{                       //�̳���Phongģ��
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
		void set_rho_bg_light(const double r);           //���ñ������������ϵ��
		void set_rho_df_light(const double r);                //������������������ϵ��
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