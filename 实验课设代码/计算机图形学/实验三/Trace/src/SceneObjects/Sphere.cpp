#include <cmath>

#include "Sphere.h"

using namespace std;


bool Sphere::intersectLocal( const ray& r, isect& i ) const
{
    // YOUR CODE HERE:
	// 光线与球面相交
    // Add sphere intersection code here.
	Vec3d A = r.getPosition();
	Vec3d D = r.getDirection();
	Vec3d C= Vec3<double>();
	double _r = 1.0;
	double a = D.length2();
	double b = 2 * (A - C) * D;
	double c = (A - C).length2() - _r;
	double delta = b * b - 4 * a * c;
    // it currently ignores all spheres and just return false.
	if (delta >= 0) {
		double t1 = (-b + sqrt(delta)) / (2 * a);
		double t2 = (-b - sqrt(delta)) / (2 * a);
		if (t1 <= RAY_EPSILON)
			return false;
		else {
			double t;
			if (t2 <= RAY_EPSILON) {
				t = t1;
				i.outsideTheObject = false;
			}
			else {
				t = t2;
				i.outsideTheObject = true;
			}
			// 焦点设置
			i.obj = this;
			i.setT(t);
			Vec3d P = r.at(t);
			Vec3d Normal = P;
			if (D*Normal > 0)
				Normal = -Normal;
			Normal.normalize();
			i.setN(Normal);
			return true;
		}
	}
    return false;
}

