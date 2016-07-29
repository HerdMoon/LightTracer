#ifndef RAY_H_
#define RAY_H_
#include "Point3D.h"
#include "Vector3D.h"

class Ray{
	public:
		Point3D o;
		Vector3D d;
		Ray();
		Ray(const Point3D&Origin,const Vector3D &dir);
	//	Ray(const Ray& ray);
	//	Ray& operator=(const Ray &rhs);
	//	~Ray();

};

#endif