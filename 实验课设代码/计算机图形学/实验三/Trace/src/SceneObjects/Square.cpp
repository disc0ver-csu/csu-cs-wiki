#include <cmath>

#include "Square.h"

using namespace std;


//Test
bool Square::intersectLocal( const ray& r, isect& i ) const
{
	Vec3d p = r.getPosition();
	Vec3d d = r.getDirection();

	if( d[2] == 0.0 ) {
		return false;
	}

	double t = -p[2]/d[2];

	if( t <= RAY_EPSILON ) {
		return false;
	}

	Vec3d P = r.at( t );

	if( P[0] < -0.5 || P[0] > 0.5 ) {	
		return false;
	}

	if( P[1] < -0.5 || P[1] > 0.5 ) {	
		return false;
	}

	i.obj = this;
	i.t = t;
	if( d[2] > 0.0 ) {
		i.N = Vec3d( 0.0, 0.0, -1.0 );
	} else {
		i.N = Vec3d( 0.0, 0.0, 1.0 );
	}

    i.setUVCoordinates( Vec2d(P[0] + 0.5, P[1] + 0.5) );
	return true;
}
