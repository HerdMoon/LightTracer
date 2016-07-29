#ifndef WORLD_H_
#define WORLD_H_

#include "GeoObj.h"
#include "tracer.h"
#include "light.h"
#include <vector>
#include "camera.h"
class viewplane
{
	public:
		int hres;                 //�����
		int vres;                 //������
		double pixelsize;

		int num_sample;        //��λ���Ӳ�����

		int max_depth;         //����������

		double gamma;             //������ʾɫ��
		void sethres(int h);
		void setvres(int v);
		void setpixelsize(double s);
		void setdepth(int n);
		void setgamma(double g);
		void setsample_num(int s);
};

inline void viewplane::sethres(int h)
{
	hres = h;
}

inline void viewplane::setvres(int v)
{
	vres = v;
} 

inline void viewplane::setpixelsize(double s)
{
	pixelsize = s;
}

inline void viewplane::setgamma(double g)
{
	gamma = g;
}

inline void viewplane::setdepth(int n)
{
	max_depth = n;
}

inline void viewplane::setsample_num(int s)
{
	num_sample = s;
}

class world{
	public:
	   viewplane vp;
	   RGBColor bg_color;
	   light* env_light;
	   
	   vector<GeometricObject*> object;
	   vector<light*> lights;

	   tracer * tracer_ptr;
	   camera* camera_ptr;

	   world();
	   void build();
	   void add_object(GeometricObject * object_ptr);
	   void add_light(light* light_ptr);

	   void delete_object();
	   void delete_lights();

	   void set_camera(camera * cam_ptr);

	   ShadeRec hit_objects(const Ray & ray) ;

	  
	   void display_pixel(const int row,const int colum,const RGBColor& pixel_color) const;
};

#endif