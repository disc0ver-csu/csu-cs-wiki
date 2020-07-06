#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera
{
public:
    Camera();
    void rayThrough( double x, double y, ray &r );
    void setEye( const Vec3d &eye );
    void setLook( double, double, double, double );
    void setLook( const Vec3d &viewDir, const Vec3d &upDir );
    void setFOV( double );
    void setAspectRatio( double );
	bool setLookSimple( const Vec3d &v, const Vec3d &pos );

    double getAspectRatio() { return aspectRatio; }

	const Vec3d& getEye() const			{ return eye; }
	const Vec3d& getLook() const		{ return look; }
	const Vec3d& getU() const			{ return u; }
	const Vec3d& getV() const			{ return v; }
private:
    Mat3d m;                     // rotation matrix
    double normalizedHeight;    // dimensions of image place at unit dist from eye
    double aspectRatio;
    
    void update();              // using the above three values calculate look,u,v
    
    Vec3d eye;
    Vec3d look;                  // direction to look
    Vec3d u,v;                   // u and v in the 
};

#endif
