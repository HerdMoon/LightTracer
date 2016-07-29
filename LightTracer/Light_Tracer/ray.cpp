#include "stdafx.h"
#include "ray.h"

Ray::Ray()
{
	o  = Point3D(0);
	d  = Vector3D(0);
}

Ray::Ray(const Point3D&Origin,const Vector3D &dir)
{
	o =Origin;
	d = dir;
}