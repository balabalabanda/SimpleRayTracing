#ifndef HITABLEH
#define HITABLEH

#include "Ray.h"

class Material;

struct HitRecord {
	double t;
	Vec3 p;
	Vec3 normal;
	Material *matPtr;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord &rec) const = 0;
};

#endif // !HITABLEH