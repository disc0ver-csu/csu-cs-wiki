#include "camera.h"

#define PI 3.14159265359
#define SHOW(x) (cerr << #x << " = " << (x) << "\n")

using namespace std;

Camera::Camera()
{
    aspectRatio = 1;
    normalizedHeight = 1;
    
    eye = Vec3d(0,0,0);
    u = Vec3d( 1,0,0 );
    v = Vec3d( 0,1,0 );
    look = Vec3d( 0,0,-1 );
}

void
Camera::rayThrough( double x, double y, ray &r )
// Ray through normalized window point x,y.  In normalized coordinates
// the camera's x and y vary both vary from 0 to 1.
{
    x -= 0.5;
    y -= 0.5;
    Vec3d dir = look + x * u + y * v;
	dir.normalize();
    r = ray( eye, dir, ray::VISIBILITY );
}

void
Camera::setEye( const Vec3d &eye )
{
    this->eye = eye;
}

void
Camera::setLook( double r, double i, double j, double k )
// Set the direction for the camera to look using a quaternion.  The
// default camera looks down the neg z axis with the pos y axis as up.
// We derive the new look direction by rotating the camera by the
// quaternion rijk.
{
                                // set look matrix
    m[0][0] = 1.0 - 2.0 * (i * i + j * j);
    m[0][1] = 2.0 * (r * i - j * k);
    m[0][2] = 2.0 * (j * r + i * k);
    
    m[1][0] = 2.0 * (r * i + j * k);
    m[1][1]= 1.0 - 2.0 * (j * j + r * r);
    m[1][2] = 2.0 * (i * j - r * k);
    
    m[2][0] = 2.0 * (j * r - i * k);
    m[2][1] = 2.0 * (i * j + r * k);
    m[2][2] = 1.0 - 2.0 * (i * i + r * r);

    update();
}

void
Camera::setLook( const Vec3d &viewDir, const Vec3d &upDir )
{
    Vec3d z = -viewDir;          // this is where the z axis should end up
    const Vec3d &y = upDir;      // where the y axis should end up
    Vec3d x = y ^ z;               // lah,

    m = Mat3d( x[0],x[1],x[2],y[0],y[1],y[2],z[0],z[1],z[2] ).transpose();

    update();
}

void
Camera::setFOV( double fov )
// fov - field of view (height) in degrees    
{
    fov /= (180.0 / PI);      // convert to radians
    normalizedHeight = 2 * tan( fov / 2 );
    update();
}

void
Camera::setAspectRatio( double ar )
// ar - ratio of width to height
{
    aspectRatio = ar;
    update();
}

void
Camera::update()
{
    u = m * Vec3d( 1,0,0 ) * normalizedHeight*aspectRatio;
    v = m * Vec3d( 0,1,0 ) * normalizedHeight;
    look = m * Vec3d( 0,0,-1 );
}

bool
Camera::setLookSimple( const Vec3d &v, const Vec3d &pos)
{
        Vec3d top = Vec3d(0,1,0);
        Vec3d out;
        Vec3d upDir;
        Vec3d viewDir;
        viewDir = v - pos;
        if (viewDir.length2() == 0)
                return false;

        viewDir.normalize();
        if (viewDir.n[0] == 0 && viewDir.n[2] == 0) {
                setLook(viewDir, Vec3d(1,0,0));
                return true;
        }
        else {
                out = viewDir ^ top;
                out.normalize();
                upDir = out ^ viewDir;
                upDir.normalize();
                setLook(viewDir, upDir);
                return true;
        }
}




