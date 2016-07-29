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

class Lambert :public brdf                     //Lambert就是完全漫反射模型，无论入射光线为何，出射都是整个平面
{
	public:
		Lambert();
		virtual RGBColor f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const;
		virtual RGBColor rho(const ShadeRec & sr,Vector3D & l_in) const;
		void set_l(double l);
		void set_c(RGBColor c);

    private:
	   double  rho_l;                //漫反射系数
	   RGBColor rho_c;               //漫反射色系数
};

class GlossySpecular : public brdf              //GlossySpecular是带高光项的Phong模型
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
		double rho_l;         //镜面反射系数
		RGBColor rho_c;       //镜面反射色系数
};

class TX_Lambertian: public brdf{
	public:
		TX_Lambertian();
		virtual RGBColor f(const ShadeRec & sr,const Vector3D& l_in,const Vector3D & l_out) const;
		virtual RGBColor rho(const ShadeRec & sr,Vector3D & l_in) const;
		void set_l(double l);

    private:
	   double  rho_l;                //漫反射系数
	   texture* rho_c;               //漫反射色系数
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