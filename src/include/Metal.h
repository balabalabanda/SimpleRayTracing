#ifndef METALH
#define METALH

#include "Material.h"

class Metal :public Material {
public:
	Metal(const Vec3 &a, double f) :albedo(a) { if (f < 1)fuzz = f; else fuzz = 1; }
	virtual bool scater(const Ray &rIn, HitRecord &rec, Vec3 &attenuation, Ray &scatterd) const {
		Vec3 reflected = reflect(unit_vector(rIn.d()), rec.normal);
		scatterd = Ray(rec.p, reflected + fuzz * randomInUnitSphere());
		attenuation = albedo;
		return (dot(scatterd.d(), rec.normal) > 0); //�ڲ���Ϊû�з���
	}

	Vec3 albedo;    //������ɫ
	double fuzz;   //����ģ������
};

#endif // !METALH
