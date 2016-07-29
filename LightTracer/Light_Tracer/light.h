#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vector3D.h"
#include "shaderec.h"

class light{
	public:
		light();
		virtual Vector3D get_dir(ShadeRec& sr) const = 0;
		virtual RGBColor get_lum(ShadeRec& sr) const = 0;
		virtual bool shadow_check(const Ray&ray,const ShadeRec & sr) const = 0;
		virtual bool get_sha() = 0;
		virtual void set_sha(bool s) = 0;
protected:
	bool shadow_exist;
};

class bg_light:public light{
	public:
		bg_light();
		void set_lum(double r);
		virtual Vector3D get_dir(ShadeRec& sr) const;
		virtual RGBColor get_lum(ShadeRec& sr) const;
		virtual bool shadow_check(const Ray&ray,const ShadeRec & sr) const;
		virtual bool get_sha();
		virtual void set_sha(bool s);
	private:
		double l;       //环境光亮度
		RGBColor color_bg; //环境光色彩

};

class pt_light:public light{
	public:
		pt_light();
		virtual Vector3D get_dir(ShadeRec& sr) const;
		virtual RGBColor get_lum(ShadeRec& sr) const;
		virtual bool shadow_check(const Ray&ray,const ShadeRec & sr) const;
		void set_loc(double x,double y,double z);
		void set_lum(double r);
		virtual bool get_sha();
		virtual void set_sha(bool s);

	private:
		double l;       //点光源亮度
		RGBColor color_pt; //点光源色彩
		Point3D loc;     //点光源位置 

};


#endif 