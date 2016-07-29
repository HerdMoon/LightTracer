#include "stdafx.h"
#include "world.h"
#include "ray.h"
#include "constant.h"
#include <highgui.h>
#include <opencv.hpp>
#include <cstdio>
#include "Material.h"
#include "Maths.h"
using namespace cv;
using namespace std;
world::world():bg_color(black),tracer_ptr(NULL),camera_ptr(NULL),env_light(new bg_light){delete_object();delete_lights();}

void world::add_object(GeometricObject * object_ptr)
{
	object.push_back(object_ptr);
}

void world::add_light(light* light_ptr)
{
	lights.push_back(light_ptr);
}

void world::delete_object()
{
	int n = object.size();
	for (int i = 0;i<n;i++)
	{
		delete object[i];
		object[i] = NULL;
	}
	object.erase(object.begin(),object.end());
}

void world::delete_lights()
{
	int n = lights.size();
	for (int i=0;i<n;i++)
	{
		delete lights[i];
		lights[i] = NULL;
	}
	lights.erase(lights.begin(),lights.end());
}

ShadeRec  world::hit_objects(const Ray & ray) 
{
	ShadeRec sr(*this);
	double t;
	Normal normal;
	Point3D local_hit_point;
	double tmin = BIG;
	int num = object.size();
//	FILE * out_file;
//	fopen_s(&out_file,"k:\\sample.txt","a+");

	for (int j = 0;j<num;j++)
	{
		if (object[j]->hit(ray,t,sr)&& (t<tmin))
		{
			sr.hit_an_object = true;
			sr.mat_ptr = object[j]->get_material();
			sr.hit_point = ray.o + t*ray.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
			tmin = t;
		}
	}

	if (sr.hit_an_object)
	{
		normal.normalize();
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
//		fprintf(out_file,"%f %f %f\n",local_hit_point.x,local_hit_point.y,local_hit_point.z);
	}
//	fclose(out_file);
	return (sr);

}

void world::build()
{
	vp.sethres(600);
	vp.setvres(400);
	vp.setpixelsize(1);
	vp.setgamma(1.0);
	vp.setsample_num(16);
	vp.setdepth(1);

	bg_color = RGBColor(0.15);
	tracer_ptr = new Whitted(this);

	bg_light* bg_light_ptr = new bg_light;
	bg_light_ptr ->set_lum(0.5);
	env_light = bg_light_ptr;

	pt_light* light_ptr = new pt_light;
	light_ptr->set_loc(150,150,0);
	light_ptr->set_lum(3.0);
	light_ptr->set_sha(true);
	add_light(light_ptr);

	sta_camera * ca_ptr = new sta_camera;
	ca_ptr ->set_eye(Point3D(75,40,100));
	ca_ptr ->set_lookat(Point3D(-10,39,0));
	ca_ptr ->set_d(360);
	ca_ptr ->trans_set();
	set_camera(ca_ptr);

	Mirror_mat *  mirror_ptr1 = new Mirror_mat;
	mirror_ptr1 ->set_rho_bg_light(0.25);
	mirror_ptr1 ->set_rho_df_light(0.75);
	mirror_ptr1 ->set_c_light(RGBColor(0.75,0.75,0));
	mirror_ptr1 ->set_ks_sp_light(RGBColor(0.15,0.15,0.15));
	mirror_ptr1 ->set_exp_sp_light(100);
	mirror_ptr1 ->set_rl_rf_light(0.75);
	mirror_ptr1 ->set_rc_rf_light(white);

	float radius = 23.0;
	sphere* sphere_ptr1 = new sphere(Point3D(38, radius, -25), radius); 
	sphere_ptr1->set_material(mirror_ptr1);
	add_object(sphere_ptr1);

	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->set_rho_bg_light(0.45); 
	matte_ptr1->set_rho_df_light(0.75);
	matte_ptr1->set_c_light(RGBColor(0.75, 0.25, 0));

	sphere* sphere_ptr2 = new sphere(Point3D(-7, 10, 42), 20);
	sphere_ptr2->set_material(matte_ptr1);      
	add_object(sphere_ptr2);
	
	Mirror_mat *  mirror_ptr3 = new Mirror_mat;
	mirror_ptr3 ->set_rho_bg_light(0.35);
	mirror_ptr3 ->set_rho_df_light(0.5);
	mirror_ptr3 ->set_c_light(RGBColor(0,0.5,0.75));
	mirror_ptr3 ->set_ks_sp_light(RGBColor(0.2));
	mirror_ptr3 ->set_exp_sp_light(100);
	mirror_ptr3 ->set_rl_rf_light(0.75);
	mirror_ptr3 ->set_rc_rf_light(white);
	
	double bottom 			= 0.0;
	double top 				= 85;   
	double cylinder_radius	= 22;
	Str_Cylinder * cylinder_ptr = new Str_Cylinder(bottom, top, cylinder_radius);
	cylinder_ptr->set_mat(mirror_ptr3);
	add_object(cylinder_ptr);

	TX_Matte*  tx_matte_ptr = new TX_Matte;
	tx_matte_ptr->set_rho_bg_light(0.30);
	tx_matte_ptr->set_rho_df_light(0.9);

	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_material(tx_matte_ptr);
	add_object(plane_ptr);


	Trans_Mat* glass_ptr = new Trans_Mat;
	glass_ptr->set_ks_sp_light(0);
	glass_ptr->set_exp_sp_light(100.0);
	glass_ptr->set_rl_eta_light(0.75);		
	glass_ptr->set_rl_rf_light(0.1);
	glass_ptr->set_rc_kt_light(RGBColor(0.9));
	glass_ptr->set_rho_bg_light(0);
	glass_ptr->set_rho_df_light(0);
	glass_ptr->set_c_light(RGBColor(0.0));
	glass_ptr->set_rc_rf_light(white);
	
	sphere* sphere_ptr4 = new sphere(Point3D(20,40, 60), 6);
	sphere_ptr4->set_material(glass_ptr);
	add_object(sphere_ptr4);

}

void world::set_camera(camera * cam_ptr)
{
	camera_ptr = cam_ptr;
}

