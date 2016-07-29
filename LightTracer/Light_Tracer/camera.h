#ifndef CAMERA_H_
#define CAMERA_H_

#include "Point3D.h"
#include "Point2D.h"
#include "Vector3D.h"

class world;

class camera {
	public:
		camera();
		void trans_set();
		void set_eye(Point3D e);
		void set_lookat(Point3D l);
		virtual void render_scene(world &w) = 0;

	protected:
		Point3D eye;                 //视点
		Point3D lookat;              //观察点
		Vector3D up;                 //旋转向量
		Vector3D u,v,w;              //观察坐标
};

class sta_camera:public camera
{
	public:
		sta_camera();
		Vector3D ray_dir(const Point2D &p) const;
		void set_d(double dr);
		virtual void render_scene(world &w);
	private:
		double d;                     //视点与观察平面的距离
		double zoom;                  //视点放缩系数
};


#endif