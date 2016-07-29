#ifndef BRDF_H_
#define BRDF_H_

#include "utility.h"
#include "shaderec.h"
#include "Vector3D.h"
#include "texture.h"
class brdf
{
    public:
		virtual RGBColor f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const = 0;
		virtual RGBColor rho(const ShadeRec & sr,Vector3D & l_in) const = 0;
};

class Lambert :public brdf                     //Lambert������ȫ������ģ�ͣ������������Ϊ�Σ����䶼������ƽ��
{
	public:
		Lambert();
		virtual RGBColor f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const;
		virtual RGBColor rho(const ShadeRec & sr,Vector3D & l_in) const;
		void set_l(double l);
		void set_c(RGBColor c);

    private:
	   double  rho_l;                //������ϵ��
	   RGBColor rho_c;               //������ɫϵ��
};

class GlossySpecular : public brdf              //GlossySpecular�Ǵ��߹����Phongģ��
{
	public:
	  GlossySpecular();
	  virtual RGBColor f(const ShadeRec & sr,const Vector3D &l_in , const Vector3D & l_out) const;
	  virtual RGBColor rho(const ShadeRec & sr,Vector3D & l_in) const;
	  void set_e(double l);
	  void set_c(RGBColor c);
	private:
		double exp;
		RGBColor rho_c;
};

class MirrorSpecular :public brdf
{
	public:
		MirrorSpecular();
	    virtual RGBColor f(const ShadeRec & sr,const Vector3D &l_in , const Vector3D & l_out) const;
	    virtual RGBColor rho(const ShadeRec & sr,Vector3D & l_in) const;
		RGBColor sample_f(const ShadeRec &sr,const Vector3D &l_out,Vector3D &l_in) const;
		void set_l(double l);
		void set_c(RGBColor c);
	private:
		double rho_l;         //���淴��ϵ��
		RGBColor rho_c;       //���淴��ɫϵ��
};

class TX_Lambertian: public brdf{
	public:
		TX_Lambertian();
		virtual RGBColor f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const;
		virtual RGBColor rho(const ShadeRec & sr,Vector3D & l_in) const;
		void set_l(double l);

    private:
	   double  rho_l;                //������ϵ��
	   texture* rho_c;               //������ɫϵ��
};
/*
class global_Lambertian: public brdf{
	public:
		global_Lambertian();
		virtual RGBColor f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const;
		virtual RGBColor rho(const ShadeRec & sr,Vector3D & l_in) const;
		void set_l(double l);
	private:
		double rho_l;
		round_texture* rho_c;
}*/


#endif