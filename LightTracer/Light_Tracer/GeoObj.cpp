#include "stdafx.h"
#include "GeoObj.h"
#include "utility.h"
#include "Point3D.h"
#include "constant.h"
#include "Vector3D.h"
#include "Normal.h"
#include <math.h>
using namespace std;

RGBColor GeometricObject::get_color()
{
	return color;
}

void GeometricObject::set_color(float r,float g,float b)
{
	color =  RGBColor(r,g,b);
}

material* GeometricObject::get_material()
{
	return mat_ptr;
}

void GeometricObject::set_material(material * m_ptr)
{
	mat_ptr = m_ptr;
}

Plane::Plane(const Point3D p,const Normal & n):normal(n),point(p),kEpsilon(1e-6){}


bool Plane::hit(const Ray& ray,double & tmin,ShadeRec & sr)
{
	double t = (point - ray.o) * normal /(ray.d * normal);
	if (t>kEpsilon)
	{
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = ray.o + ray.d * t;
		return true;
	}
	else
	{
		return false;
	}
	

}

bool Plane::shadow_hit(const Ray&ray,double &tmin)
{
	double t = (point - ray.o) * normal /(ray.d * normal);
	if (t>kEpsilon)
	{
		tmin = t;
		return true;
	}
	else
	{
		return false;
	}
}

sphere::sphere():center(0),radius(0),kEpsilon(1e-6){}

sphere::sphere(Point3D cent,double ra):center(cent),radius(ra),kEpsilon(1e-6){}


bool sphere::hit(const Ray&ray,double & tmin,ShadeRec & sr)
{
	double t;
	Vector3D temp = ray.o - center;
	double a = ray.d * ray.d;
	double b = 2 * temp *ray.d;
	double c = temp*temp -radius *radius;
	double disc = b*b- 4*a*c;
	if (disc<0.0) return false;
	else
	{
		double e = sqrt(disc);
		double denom = 2*a;
		t = (-b-e)/denom;
		if (t>kEpsilon)
		{
			tmin = t;
			sr.normal = (temp+t*ray.d);
			sr.local_hit_point = ray.o + t*ray.d;
			return true;
		}
		t = (-b+e) /denom;
		if (t>kEpsilon)
		{
			tmin = t;
			sr.normal = (temp+t*ray.d) / radius;
			sr.local_hit_point = ray.o + t*ray.d;
			return true;
		}
	}

	return false;
}

bool sphere::shadow_hit(const Ray&ray,double &tmin)
{
	double t;
	Vector3D temp = ray.o - center;
	double a = ray.d * ray.d;
	double b = 2 * temp *ray.d;
	double c = temp*temp -radius *radius;
	double disc = b*b- 4*a*c;
	if (disc<0.0) return false;
	else
	{
		double e = sqrt(disc);
		double denom = 2*a;
		t = (-b-e)/denom;
		if (t>kEpsilon)
		{
			tmin = t;
			return true;
		}
		t = (-b+e) /denom;
		if (t>kEpsilon)
		{
			tmin = t;
			return true;
		}
	}

	return false;	
}

disk::disk():center(0),normal(0,0,1),radius(1),kEpsilon(1e-6){}
disk::disk(Point3D p,double r,Normal n):center(p),radius(r),normal(n),kEpsilon(1e-6){}

bool disk::hit(const Ray&ray,double & tmin,ShadeRec & s)
{
	double t = (center - ray.o) * normal /(ray.d * normal);

	if (t<=kEpsilon)
	{
		return false;
	}

	Point3D p = ray.o + t*ray.d;
	if (center.d_squared(p) < radius*radius)
	{
		tmin = t;
		s.normal = normal;
		s.local_hit_point = ray.o + ray.d * t;
		return true;
	}
	else
	{
		return false;
	}
}

bool disk::shadow_hit(const Ray&ray,double &tmin) 
{
	double t = (center - ray.o) * normal /(ray.d * normal);

	if (t<=kEpsilon)
	{
		return false;
	}

	Point3D p = ray.o + t*ray.d;
	if (center.d_squared(p) < radius*radius)
	{
		tmin = t;

		return true;
	}
	else
	{
		return false;
	}
}

void compound::delete_object()
{
	int n = objects.size();
	for (int i=0;i<n;i++)
	{
		delete objects[i];
		objects[i] = NULL;
	}
	objects.erase(objects.begin(),objects.end());
}

compound::compound(){delete_object();}
void compound::add_object(GeometricObject* object_ptr)
{
	objects.push_back(object_ptr);
}

bool compound::hit(const Ray &ray, double &tmin,ShadeRec &sr)
{
	double t;
	Normal normal;
	Point3D local_hit_point;
	bool hit = false;
	tmin = BIG;

	int num_obj = objects.size();

	for (int i=0;i< num_obj;i++)
	{
		if (objects[i]->hit(ray,t,sr) && (t<tmin))
		{
			hit = true;
			tmin = t;
			mat_ptr = objects[i]->get_material();
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	}
	if (hit)
	{
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
	return (hit);
}

bool compound::shadow_hit(const Ray&ray,double &tmin)
{
	double t;
	bool hit = false;
	tmin = BIG;

	int num_obj = objects.size();

	for (int i=0;i< num_obj;i++)
	{
		if (objects[i]->shadow_hit(ray,t) && (t<tmin))
		{
			hit = true;
			tmin = t;
		}
	}
	return (hit);
}

void compound::set_mat(material * mat_ptr_spec)
{
	int num_obj = objects.size();
	for (int i=0;i< num_obj;i++)
	{
		objects[i]->set_material(mat_ptr_spec);
	}
	mat_ptr = mat_ptr_spec;
}

open_cylinder::open_cylinder(double bottom,double top,double radius):bottom(bottom),top(top),radius(radius),kEpsilon(1e-6)
{
}

bool open_cylinder::hit(const Ray&ray,double & tmin,ShadeRec & s)
{
	double a = (ray.d.x * ray.d.x + ray.d.z * ray.d.z);
	double b = 2*(ray.o.x * ray.d.x+ ray.o.z * ray.d.z);
	double c = (ray.o.x * ray.o.x+ray.o.z*ray.o.z - radius * radius);
	Point3D local_hit;
	if (b*b - 4*a*c < 1e-6)
	{
		return (false);
	}
	double t;
	t = (-b - sqrt(b*b-4*a*c)) / (2*a);
	if (t > kEpsilon)
	{
		local_hit = ray.o + t * ray.d;
		if ((local_hit.y < top) && (local_hit.y > bottom))
		{
			tmin = t;
			s.local_hit_point = local_hit;
			s.normal = Normal(local_hit.x / radius,0,local_hit.z / radius);
			return true;
		}
	}

	t = (-b + sqrt(b*b-4*a*c)) / (2*a);
	if (t > kEpsilon)
	{
		local_hit = ray.o + t * ray.d;
		if ((local_hit.y < top) && (local_hit.y > bottom))
		{
			tmin = t;
			s.local_hit_point = local_hit;
			s.normal = Normal(local_hit.x / radius,0,local_hit.z / radius);
			return true;
		}
	}
	return false;
}

bool open_cylinder::shadow_hit(const Ray&ray,double &tmin) 
{
	double a = (ray.d.x * ray.d.x + ray.d.z * ray.d.z);
	double b = 2*(ray.o.x * ray.d.x+ ray.o.z * ray.d.z);
	double c = (ray.o.x * ray.o.x+ray.o.z*ray.o.z - radius * radius);
	Point3D local_hit;
	if (b*b - 4*a*c < 0)
	{
		return (false);
	}
	double t;
	t = (-b - sqrt(b*b-4*a*c)) / (2*a);
	if (t > kEpsilon)
	{
		local_hit = ray.o + t * ray.d;
		if ((local_hit.y < top) && (local_hit.y > bottom))
		{
			tmin = t;
			return true;
		}
	}

	t = (-b + sqrt(b*b-4*a*c)) / (2*a);
	if (t > kEpsilon)
	{
		local_hit = ray.o + t * ray.d;
		if ((local_hit.y < top) && (local_hit.y > bottom))
		{
			tmin = t;
			return true;
		}
	}
	return false;
}

Str_Cylinder::Str_Cylinder(const double bottom,const double top,const double radius):compound()
{
	objects.push_back(new disk(Point3D(0,bottom,0),radius,Normal(0,-1,0)));
	objects.push_back(new disk(Point3D(0,top,0),radius,Normal(0,1,0)));
	objects.push_back(new open_cylinder(bottom,top,radius));
}
bool Str_Cylinder::hit(const Ray &ray, double &tmin,ShadeRec &sr)
{
	return (compound::hit(ray,tmin,sr));
}


bool Str_Cylinder::shadow_hit(const Ray&ray,double &tmin)
{
	return (compound::shadow_hit(ray,tmin));
}