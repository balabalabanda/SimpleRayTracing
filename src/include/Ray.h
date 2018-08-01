#ifndef RAYH
#define RAYH
#include "Vec3.h"

class Ray {
public:
	Ray() {}
	Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }
	Vec3 o() const { return A; }
	Vec3 d() const { return B; }
	Vec3 p(double t) const {return A + t * B; }

	Vec3 A;
	Vec3 B;
};

#endif