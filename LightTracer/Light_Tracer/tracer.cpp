#include "stdafx.h"
#include "tracer.h"
#include "constant.h"
#include "ray.h"
#include "shaderec.h"
#include "world.h"
#include "Material.h"

tracer::tracer():world_ptr(NULL){}
tracer::tracer(world* w_ptr):world_ptr(w_ptr) {}



RGBColor tracer::trace_ray(const Ray& ray) const
{
	return (black);
}

RGBColor tracer::trace_ray(const Ray& ray,const int depth) const
{
	return (black);
}

MultipleObjects::MultipleObjects(void)
	: tracer()
{}


// -------------------------------------------------------------------- constructor
		
MultipleObjects::MultipleObjects(world* _worldPtr)
	: tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

MultipleObjects::~MultipleObjects(void) {}


// -------------------------------------------------------------------- trace_ray

RGBColor	
MultipleObjects::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
		
	if (sr.hit_an_object)   
		return (sr.color);   
	else
		return (world_ptr->bg_color);
}

Ray_cast::Ray_cast():tracer(){}
Ray_cast::Ray_cast(world* w_ptr):tracer(w_ptr){}

RGBColor Ray_cast::trace_ray(const Ray& ray,const int depth) const
{
	ShadeRec sr(world_ptr ->hit_objects(ray)); 
	if (sr.hit_an_object)
	{
		sr.ray = ray;
		return (sr.mat_ptr->shade(sr));
	}
	else
		return (world_ptr ->bg_color);

}

Whitted::Whitted():tracer(){}
Whitted::Whitted(world* w_ptr):tracer(w_ptr){}

RGBColor Whitted::trace_ray(const Ray&ray,const int depth) const
{
	if (depth >world_ptr ->vp.max_depth)
		return black;
	else
	{
		ShadeRec sr(world_ptr->hit_objects(ray));

		if (sr.hit_an_object)
		{
			sr.depth = depth;
			sr.ray = ray;
			return (sr.mat_ptr->shade(sr));
		}
		else
			return (world_ptr->bg_color);
	}
}