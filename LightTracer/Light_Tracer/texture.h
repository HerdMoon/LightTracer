#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "utility.h"
#include "shaderec.h"
#include <highgui.h>
#include <cv.h>
using namespace cv;

class texture {
	public:
		virtual RGBColor get_color(const ShadeRec sr);      //��ȡshaderec����color.
};

class chess :public texture{
	public:
		virtual RGBColor get_color(const ShadeRec sr);
};
/*
class round_texture:public texture{
	public:
		virtual RGBColor get_color(const ShadeRec sr);
		IplImage * img;

};
*/
#endif