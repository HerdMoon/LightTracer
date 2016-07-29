#ifndef TRACER_H_
#define TRACER_H_

class world;

#include "utility.h"
#include "ray.h"

class tracer
{
public:
	tracer();
	tracer(world* w_ptr);
	virtual ~tracer(){}
	virtual RGBColor trace_ray(const Ray& ray)const;
	virtual RGBColor trace_ray(const Ray& ray,const int depth) const;
protected:
	world* world_ptr;

};


class MultipleObjects: public tracer {
	public:
							
		MultipleObjects();
		MultipleObjects(world* _world_ptr);				
	
		virtual											
		~MultipleObjects(void);
						
		virtual RGBColor	
		trace_ray(const Ray& ray) const;
};

class Ray_cast:public tracer{
	public:
		Ray_cast();
		Ray_cast(world* w_ptr);
		virtual RGBColor trace_ray(const Ray& ray,const int depth) const;
};

class Whitted:public tracer{
	public:
	  Whitted();
	  Whitted(world* w_ptr);
	  virtual RGBColor trace_ray(const Ray& ray,const int depth) const;
};

#endif