#include <iostream>
#include <graphics.h>
#include "Sphere.h"
#include "HitableList.h"
#include <float.h>
#include <thread>
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "dielectric.h"
using namespace std;


Vec3 color(const Ray& r,Hitable *world,int depth) {
	HitRecord rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		Ray scattered;
		Vec3 attenuation;

		//计算碰撞材质的反射光线方向和衰减系数
		if (depth < 50 && rec.matPtr->scater(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return Vec3(0, 0, 0);
		}
	}
	else {
		Vec3 unitDirection = unit_vector(r.d());
		double t = 0.5*(unitDirection.y() + 1.0);
		return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

void threadRun(int xmin,int ymin,int xmax,int ymax,int nx,int ny,int ns,Camera cam,Hitable *world) {
	for (int i = xmin; i < xmax; i++) {
		for (int j = ymin; j < ymax; j++) {
			Vec3 col(0, 0, 0);
			for (int p = 0; p < ns; p++) {
				for (int q = 0; q < ns; q++) {
					double u = ((double)i + (p+rand() / 32767.0)/ns) / nx;
					double v = ((double)j + (q+rand() / 32767.0)/ns) / ny;
					Ray r = cam.getRay(u, v);
					col += color(r, world, 0);
				}
			}
			col /= (double)ns*ns;
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			putpixel(i, j, RGB(col.r() * 255, col.g() * 255, col.b() * 255));
		}
	}
}

void main() {
	int nx = 800;
	int ny = 400;
	int ns = 10; //抗锯齿程度
	initgraph(nx, ny);
	setorigin(0, ny);
	setaspectratio(1, -1);

	Hitable *list[5];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5,new Lambertian(Vec3(0.8,0.3,0.3)));
	list[1] = new Sphere(Vec3(0, -500.5, -1), 500, new Lambertian(Vec3(0.8, 0.4, 0.2)));
	list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.6, 0.6, 0.6),0));
	list[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new Dielectric(1.5));
	list[4] = new Sphere(Vec3(0.5, 1, -2.5), 1, new Metal(Vec3(0.6, 0.6, 0.6), 0));
	list[4] = new Sphere(Vec3(-0.5, 1, -2.5), 1, new Lambertian(Vec3(0.3,0.8,0.4)));
	Hitable *world = new HitableList(list, 5);
	Camera cam(Vec3(-2,2,1),Vec3(0,0,-1),Vec3(0,1,0),60,(double)nx/ny);

	////随机渲染
	//for (int k = 0; k < 1000000; k++)
	//{
	//	int i = rand() / 32767.0 * 800;
	//	int j = rand() / 32767.0 * 400;
	//	Vec3 col(0, 0, 0);
	//	for (int s = 0; s < ns; s++) {
	//		double u = ((double)i + (rand() / 32767.0)) / nx;
	//		double v = ((double)j + (rand() / 32767.0)) / ny;
	//		Ray r = cam.getRay(u, v);
	//		col += color(r, world,0);
	//	}
	//	col /= (double)ns;
	//	col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
	//	putpixel(i, j, RGB(col.r() * 255, col.g() * 255, col.b() * 255));
	//}

	//多线程渲染
	int deltax = nx / 4;
	int deltay = ny / 2;
	thread t1(threadRun, 0, 0, deltax, deltay, nx, ny, ns, cam, world);
	thread t2(threadRun, deltax * 1, 0, deltax * 2, deltay, nx, ny, ns, cam, world);
	thread t3(threadRun, deltax * 2, 0, deltax * 3, deltay, nx, ny, ns, cam, world);
	thread t4(threadRun, deltax * 3, 0, deltax * 4, deltay, nx, ny, ns, cam, world);
	thread t5(threadRun, 0, deltay, deltax, deltay * 2, nx, ny, ns, cam, world);
	thread t6(threadRun, deltax * 1, deltay, deltax * 2, deltay*2, nx, ny, ns, cam, world);
	thread t7(threadRun, deltax * 2, deltay, deltax * 3, deltay*2, nx, ny, ns, cam, world);
	thread t8(threadRun, deltax * 3, deltay, deltax * 4, deltay*2, nx, ny, ns, cam, world);
	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();
	t5.detach();
	t6.detach();
	t7.detach();
	t8.detach();

	getchar();
}