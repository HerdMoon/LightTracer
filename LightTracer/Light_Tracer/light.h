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
		double l;       //����������
		RGBColor color_bg; //������ɫ��

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
		double l;       //���Դ����
		RGBColor color_pt; //���Դɫ��
		Point3D loc;     //���Դλ�� 

};


#endif 