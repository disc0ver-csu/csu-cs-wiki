#include <cmath>

#include "Cylinder.h"

using namespace std;


bool Cylinder::intersectLocal( const ray& r, isect& i ) const
{
	i.obj = this;

	if( intersectCaps( r, i ) ) {
		isect ii;
		if( intersectBody( r, ii ) ) {
			if( ii.t < i.t ) {
				i = ii;
				i.obj = this;
			}
		}
		return true;
	} else {
		return intersectBody( r, i );
	}
}

bool Cylinder::intersectBody( const ray& r, isect& i ) const
{
	double x0 = r.getPosition()[0];
	double y0 = r.getPosition()[1];
	double x1 = r.getDirection()[0];
	double y1 = r.getDirection()[1];

	double a = x1*x1+y1*y1;
	double b = 2.0*(x0*x1 + y0*y1);
	double c = x0*x0 + y0*y0 - 1.0;

	if( 0.0 == a ) {
		// This implies that x1 = 0.0 and y1 = 0.0, which further
		// implies that the ray is aligned with the body of the cylinder,
		// so no intersection.
		return false;
	}

	double discriminant = b*b - 4.0*a*c;

	if( discriminant < 0.0 ) {
		return false;
	}
	
	discriminant = sqrt( discriminant );

	double t2 = (-b + discriminant) / (2.0 * a);

	if( t2 <= RAY_EPSILON ) {
		return false;
	}

	double t1 = (-b - discriminant) / (2.0 * a);

	if( t1 > RAY_EPSILON ) {
		// Two intersections.
		Vec3d P = r.at( t1 );
		double z = P[2];
		if( z >= 0.0 && z <= 1.0 ) {
			// It's okay.
			i.t = t1;
			i.N = Vec3d( P[0], P[1], 0.0 );
			i.N.normalize();
			return true;
		}
	}

	Vec3d P = r.at( t2 );
	double z = P[2];
	if( z >= 0.0 && z <= 1.0 ) {
		i.t = t2;

		Vec3d normal( P[0], P[1], 0.0 );
		// In case we are _inside_ the _uncapped_ cone, we need to flip the normal.
		// Essentially, the cone in this case is a double-sided surface
		// and has _2_ normals
		if( !capped && (normal * r.getDirection()) > 0 )
			normal = -normal;

		i.N = normal;
		i.N.normalize();
		return true;
	}

	return false;
}

bool Cylinder::intersectCaps( const ray& r, isect& i ) const
{
	if( !capped ) {
		return false;
	}

	double pz = r.getPosition()[2];
	double dz = r.getDirection()[2];

	if( 0.0 == dz ) {
		return false;
	}

	double t1;
	double t2;

	if( dz > 0.0 ) {
		t1 = (-pz)/dz;
		t2 = (1.0-pz)/dz;
	} else {
		t1 = (1.0-pz)/dz;
		t2 = (-pz)/dz;
	}

	if( t2 < RAY_EPSILON ) {
		return false;
	}

	if( t1 >= RAY_EPSILON ) {
		Vec3d p( r.at( t1 ) );
		if( (p[0]*p[0] + p[1]*p[1]) <= 1.0 ) {
			i.t = t1;
			if( dz > 0.0 ) {
				// Intersection with cap at z = 0.
				i.N = Vec3d( 0.0, 0.0, -1.0 );
			} else {
				i.N = Vec3d( 0.0, 0.0, 1.0 );
			}
			return true;
		}
	}

	Vec3d p( r.at( t2 ) );
	if( (p[0]*p[0] + p[1]*p[1]) <= 1.0 ) {
		i.t = t2;
		if( dz > 0.0 ) {
			// Intersection with interior of cap at z = 1.
			i.N = Vec3d( 0.0, 0.0, 1.0 );
		} else {
			i.N = Vec3d( 0.0, 0.0, -1.0 );
		}
		return true;
	}

	return false;
}
