#ifndef DIELECTRICH
#define DIELECTRICH
#include "Material.h"

//���亯��	 �������	    ����(��������)	������֮��		�������
bool refract(const Vec3 &v, const Vec3 &n, double niOvernt, Vec3 &refracted) {
	Vec3 uv = unit_vector(v);
	double dt = dot(uv, n);
	double discriminant = 1.0 - niOvernt * niOvernt*(1 - dt * dt); //�����б�ʽȷ�����޷������
	if (discriminant > 0) {
		refracted = niOvernt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else {
		return false;
	}
}

//�Է�������ʽ�Ľ���
double schlick(double cosine, double refIdx) {
	double r0 = (1 - refIdx) / (1 + refIdx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}

//����ʲ��ʣ�������Ч��
class Dielectric :public Material {
public:
	Dielectric(double ri,Vec3 att = Vec3(1,1,1)):refIdx(ri), attenuation(att){}
	virtual bool scater(const Ray &rIn, HitRecord &rec, Vec3 &attenuation, Ray &scatterd) const {
		Vec3 outwardNormal;
		Vec3 reflected = reflect(rIn.d(), rec.normal);
		double niOvernt;
		attenuation = this->attenuation;     //˥��ϵ��Ĭ��Ϊ0
		Vec3 refracted;
		double reflectProb;     //�������
		double cosine;
		if (dot(rIn.d(), rec.normal) > 0) {   //�жϴӿ������뻹�Ǵ������ڲ����
			outwardNormal = -rec.normal;
			niOvernt = refIdx;
			double tempCos = dot(rIn.d(), rec.normal) / rIn.d().length();
			cosine = (refIdx*refIdx + tempCos * tempCos - 1) / refIdx * refIdx;
		}
		else {
			outwardNormal = rec.normal;
			niOvernt = 1.0 / refIdx;
			cosine = -dot(rIn.d(), rec.normal) / rIn.d().length();
		}
		if (refract(rIn.d(), outwardNormal, niOvernt, refracted)) {
			reflectProb = schlick(cosine, refIdx);
		}
		else {
			reflectProb = 1.0;
		}
		if (Random() < reflectProb) {
			scatterd = Ray(rec.p, reflected);
		}
		else {
			scatterd = Ray(rec.p, refracted);
		}
		return true;
	}

	Vec3 attenuation;
	double refIdx;         //����������
};


#endif // !DIELECTRICH

