#include <cmath>

#include "light.h"


using namespace std;

double DirectionalLight::distanceAttenuation( const Vec3d& P ) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


Vec3d DirectionalLight::shadowAttenuation( const Vec3d& P ) const
{
    // YOUR CODE HERE:
	Vec3d d = getDirection(P);
	isect i;
	ray shadowRay(P, d);
	if (this->getScene()->intersect(shadowRay, i)) {
		return Vec3d(0, 0, 0);
	}
    // You should implement shadow-handling code here.
    return Vec3d(1,1,1);
}

Vec3d DirectionalLight::getColor( const Vec3d& P ) const
{
	// Color doesn't depend on P 
	return color;
}

Vec3d DirectionalLight::getDirection( const Vec3d& P ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation( const Vec3d& P ) const
{
	// YOUR CODE HERE

	// You'll need to modify this method to attenuate the intensity 
	// of the light based on the distance between the source and the 
	// point P.  For now, we assume no attenuation and just return 1.0
	Vec3d d = P - position;
	double r = d.length(); //¾àÀë
	return min(1.0, 1.0 / (constantTerm + linearTerm * r + quadraticTerm * r*r));
//	return 1.0;
}

Vec3d PointLight::getColor( const Vec3d& P ) const
{
	// Color doesn't depend on P 
	return color;
}

Vec3d PointLight::getDirection( const Vec3d& P ) const
{
	Vec3d ret = position - P;
	ret.normalize();
	return ret;
}


Vec3d PointLight::shadowAttenuation(const Vec3d& P) const
{
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.
	Vec3d d = getDirection(P);
	isect i;
	ray shadowRay(P, d);
	if (this->getScene()->intersect(shadowRay, i)) {
		double tLight = (P - position).length();
		if (i.t < tLight)
			return Vec3d(0, 0, 0);
		else
			return Vec3d(1, 1, 1);
	}
    return Vec3d(1,1,1);
}
