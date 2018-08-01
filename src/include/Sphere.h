#ifndef SPHEREH
#define SPHEREH

#include "Hitable.h"

class Sphere :public Hitable {
public:
	Sphere(){}
	Sphere(Vec3 cen, double r,Material *mat) :center(cen), radius(r),material(mat) {};
	virtual bool hit(const Ray &r, double tmin, double tmax, HitRecord &rec) const {
		Vec3 oc = r.o() - center;
		double a = dot(r.d(), r.d());
		double b = dot(oc, r.d());
		double c = dot(oc, oc) - radius * radius;
		double discriminant = b * b - a*c;
		if (discriminant > 0) {
			double temp = (-b - sqrt(b*b - a * c)) / a;
			if (temp<tmax&&temp>tmin) {
				rec.t = temp;
				rec.p = r.p(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.matPtr = material;
				return true;
			}
			temp = (-b + sqrt(b*b - a * c)) / a;
			if (temp<tmax&&temp>tmin) {
				rec.t = temp;
				rec.p = r.p(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.matPtr = material;
				return true;
			}
		}
		return false;
	}
	Vec3 center;
	double radius;
	Material *material;
};

#endif // !SPHEREH
