// Light_Tracer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <opencv.hpp>
#include <highgui.h>
#include "world.h"

using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	int t;
	world w;
	w.build();
	w.camera_ptr->render_scene(w);
	scanf_s("%d",&t);
	return 0;
}

