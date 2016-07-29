#ifndef GEOOBJ_H_
#define GEOOBJ_H_
#include "stdafx.h"
#include "shaderec.h"
#include "ray.h"
#include <vector>
class material;


using namespace std;
class GeometricObject{
	public:
		RGBColor get_color();
		void set_color(float r,float g,float b);

		material * get_material();
		void set_material(material* m_ptr);

		virtual bool hit(const Ray &ray, double &tmin,ShadeRec &sr) = 0;
		virtual bool shadow_hit(const Ray&ray,double &tmin) = 0;

	protected:
		RGBColor color;
		material * mat_ptr;

		
};

class Plane: public GeometricObject{
	public:
		Plane();
		Plane(const Point3D p,const Normal & n);
		virtual bool hit(const Ray& ray,double & t,ShadeRec & s);
		virtual bool shadow_hit(const Ray&ray,double &tmin);
	private:
		Point3D    point;
		Normal     normal;
		const double kEpsilon ;
};

class sphere: public GeometricObject{
	public:
		sphere();
		sphere(Point3D cent,double ra);
		virtual bool hit(const Ray&ray,double & t,ShadeRec & s);
		virtual bool shadow_hit(const Ray&ray,double &tmin);
        void set_center(Point3D p);
		void set_radius(double r);

	private:
		Point3D  center;
		double radius;
	    const double kEpsilon;
};

class disk:public GeometricObject{
	public:
		disk();
		disk(Point3D p,double r,Normal n);
		virtual bool hit(const Ray&ray,double & tmin,ShadeRec & s);
		virtual bool shadow_hit(const Ray&ray,double &tmin);		
	private:
		Point3D center;
		Normal normal;
		double radius;
		const double kEpsilon;
};

class open_cylinder:public GeometricObject{            //圆心在原点的一个直立圆柱
	public:
		open_cylinder(double bottom,double top,double radius);
		virtual bool hit(const Ray&ray,double & tmin,ShadeRec & s);
		virtual bool shadow_hit(const Ray&ray,double &tmin);	
	private:
		double bottom;
		double top;
		double radius;
		const double kEpsilon;
};

class compound:public GeometricObject{
	public:
		compound();
		virtual void set_mat(material * mat_ptr);
		void delete_object();
		void add_object(GeometricObject* object_ptr);
		virtual bool hit(const Ray &ray, double &tmin,ShadeRec &sr);
		virtual bool shadow_hit(const Ray&ray,double &tmin);

	protected:
		vector <GeometricObject*> objects;	
};


class Str_Cylinder:public compound{           //过原点的直立圆柱
	public:
		Str_Cylinder(void);
		Str_Cylinder(const double bottom,const double top,const double radius);
		virtual bool hit(const Ray &ray, double &tmin,ShadeRec &sr);
		virtual bool shadow_hit(const Ray&ray,double &tmin);

};

inline void sphere::set_center(Point3D p)
{
	center = p;
}

inline void sphere::set_radius(double r)
{
	radius = r;
}

#endif