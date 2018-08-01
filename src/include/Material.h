#ifndef MATERIALH
#define MATERIALH
#include "Ray.h"
#include "Hitable.h"

double Random() {
	return rand() / 32767.0;
}

Vec3 randomInUnitSphere() {
	Vec3 p;
	do {
		p = 2.0*Vec3(Random(), Random(), Random()) - Vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

//反射函数
Vec3 reflect(const Vec3 &v, const Vec3 &n) {
	return v - 2 * dot(v, n)*n;
}


class Material {
public:                   //入射光线                    散射光线衰减程度      散射光线
	virtual bool scater(const Ray &rIn, HitRecord &rec, Vec3 &attenuation, Ray &scatterd) const = 0;
};

#endif // !MATERIALH

