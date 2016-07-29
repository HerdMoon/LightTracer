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
		Point3D eye;                 //�ӵ�
		Point3D lookat;              //�۲��
		Vector3D up;                 //��ת����
		Vector3D u,v,w;              //�۲�����
};

class sta_camera:public camera
{
	public:
		sta_camera();
		Vector3D ray_dir(const Point2D &p) const;
		void set_d(double dr);
		virtual void render_scene(world &w);
	private:
		double d;                     //�ӵ���۲�ƽ��ľ���
		double zoom;                  //�ӵ����ϵ��
};


#endif