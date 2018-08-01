#ifndef HITABLELISTH
#define HITABLELISTH

#include "Hitable.h"

class HitableList :public Hitable {
public:
	HitableList() {}
	HitableList(Hitable **l, int n) { list = l, listSize = n; }
	virtual bool hit(const Ray& r, double tmin, double tmax, HitRecord &rec) const {
		HitRecord tempRec;
		bool hitAnything = false;
		double closetSoFar = tmax;
		for (int i = 0; i < listSize; i++) {
			if (list[i]->hit(r, tmin, closetSoFar, tempRec)) {
				hitAnything = true;
				closetSoFar = tempRec.t;
				rec = tempRec;
			}
		}
		return hitAnything;
	}

	Hitable **list; //用二级指针避免定义长度
	int listSize;
};

#endif // !HITABLELISTH

