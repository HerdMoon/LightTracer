#include "stdafx.h"
#include "camera.h"
#include "utility.h"
#include "ray.h"
#include <highgui.h>
#include <opencv.hpp>
#include "constant.h"
#include "tracer.h"
#include "Maths.h"
#include <cstdio>
#include "world.h"
using namespace cv;
using namespace std;
camera::camera():eye(Point3D(0,0,0)),lookat(Point3D(0,0,0)),up(Vector3D(0,1,0)),u(Vector3D(0,0,0)),v(Vector3D(0,0,0)),w(Vector3D(0,0,0)){}

void camera::set_eye(Point3D e)
{
	eye = e;
}

void camera::set_lookat(Point3D l)
{
	lookat = l;
}

void camera::trans_set()
{
	w =eye - lookat;
	w.normalize();
	u = up ^ w;
	u.normalize();
	v = w ^ u;
}

sta_camera::sta_camera():camera(){zoom = 1.0;}

Vector3D sta_camera::ray_dir(const Point2D &p) const
{
	Vector3D dir = p.x * u+ p.y *v -d*w;
	dir.normalize();
	return dir;
}

void sta_camera::render_scene(world &w)
{
//	FILE* di_out;
//	fopen_s(&di_out,"k:\\di.txt","a+");
	RGBColor pixel_color;
	Ray ra;
	viewplane vp(w.vp);
	Mat TGOD(vp.vres,vp.hres,CV_8UC3);

	Point2D samp_p;
	Point3D pix_p;
	
	int n = int(sqrt(float(vp.num_sample)));
	double max_c;
	max_c = 0;

	vp.pixelsize /= zoom;
	ra.o = eye;

	double x,y;
	int p;
	int q;

	double k_max_c = 1.2;

	uchar* temp;
	for (int r=0; r<vp.vres; r++)
	{
		temp = TGOD.ptr<uchar>(r);
		for (int c = 0; c<=vp.hres; c++)
		{
			if ((r==200) && (c ==300))
			{
				int ssr = 1;
			}
			pixel_color = black;
			for (p=0;p<n;p++)
			   for (q=0;q<n;q++)
			   {

				   x = vp.pixelsize * (c - 0.5*(vp.hres - 1.0)+(q+0.5)/n);
				   y = vp.pixelsize * (vp.vres-r - 0.5*(vp.vres - 1.0) - (p+0.5)/n);
				   ra.d = ray_dir(Point2D(x,y));

  

	//			   fprintf(di_out,"%f %f %f\n",ra.d.x,ra.d.y,ra.d.z);

				   RGBColor tk= w.tracer_ptr ->trace_ray(ra,0);
				   pixel_color = pixel_color+tk;

			   }
			   pixel_color = pixel_color / vp.num_sample;
			   max_c = max(max(max(max_c,pixel_color.r),pixel_color.g),pixel_color.b);
			   temp[c*3] = int(pixel_color.b/k_max_c*255);
			   temp[c*3+1] = int(pixel_color.g/k_max_c*255);
			   temp[c*3+2] = int(pixel_color.r/k_max_c *255);
		}
	}
	
	   printf("%f",max_c);
		imwrite("k:\\output.jpg",TGOD);

//	fclose(di_out);	
}

void sta_camera::set_d(double dr)
{
	d = dr;
}