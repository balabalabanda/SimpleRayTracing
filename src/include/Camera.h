#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"

class Camera {
public:
	       //垂直视域   和  长宽比
	Camera(Vec3 lookfrom,Vec3 lookat,Vec3 vup,double vfov,double aspect) {
		Vec3 u, v, w;
		double theta = vfov * M_PI / 180;
		double halfHeight = tan(theta / 2);
		double halfWidth = aspect * halfHeight;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lowerLeft = origin - halfWidth * u - halfHeight * v - w;
		horizontal = 2 * halfWidth*u;
		vertical = 2 * halfHeight*v;
		
	}

	Ray getRay(double u, double v) {
		return Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
	}

	Vec3 lowerLeft;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 origin;
};

#endif // !CAMERAH
