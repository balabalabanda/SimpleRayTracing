#ifndef LAMBERTIANH
#define LAMBERTIANH

#include "Material.h"

class Lambertian :public Material {
public:
	Lambertian(const Vec3 &a):albedo(a){}
	virtual bool scater(const Ray &rIn, HitRecord &rec, Vec3 &attenuation, Ray &scatterd) const {
		Vec3 target = rec.p + rec.normal + randomInUnitSphere();
		scatterd = Ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	Vec3 albedo; //反射率，即物体颜色
};

#endif // !LAMBERTIANH
