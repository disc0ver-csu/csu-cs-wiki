//
// ray.h
//
// The low-level classes used by ray tracing: the ray and isect classes.
//

#ifndef __RAY_H__
#define __RAY_H__

// who the hell cares if my identifiers are longer than 255 characters:
#pragma warning(disable : 4786)

#include "../vecmath/vec.h"
#include "../vecmath/mat.h"
#include "material.h"

class SceneObject;

// A ray has a position where the ray starts, and a direction (which should
// always be normalized!)

class ray {
public:
	enum RayType
	{
		VISIBILITY,
		REFLECTION,
		REFRACTION,
		SHADOW
	};


	ray( const Vec3d& pp, const Vec3d& dd, RayType tt = VISIBILITY )
		: p( pp ), d( dd ), t( tt ) {}
	ray( const ray& other ) 
		: p( other.p ), d( other.d ), t( other.t ) {}
	~ray() {}

	ray& operator =( const ray& other ) 
	{ p = other.p; d = other.d; return *this; }

	Vec3d at( float t ) const
	{ return p + (t*d); }

	Vec3d getPosition() const { return p; }
	Vec3d getDirection() const { return d; }

	RayType type() const	{ return t; }

protected:
	Vec3d p;
	Vec3d d;
	RayType t; 
};

// The description of an intersection point.

class isect
{
public:
    isect()
        : obj( NULL ), t( 0.0 ), N(), material(0) {}

    ~isect()
    {
        delete material;
    }
    
    void setObject( const SceneObject *o ) { obj = o; }
    void setT( double tt ) { t = tt; }
    void setN( const Vec3d& n ) { N = n; }
    void setMaterial( const Material& m ) 
      { if(material) *material = m; else material = new Material(m); }
    void setUVCoordinates( const Vec2d& coords )
      { uvCoordinates = coords; }
 
    isect( const isect& other )
    {
        obj = other.obj;
        t = other.t;
        N = other.N;
        uvCoordinates = other.uvCoordinates;
        if( other.material )
          material = new Material( *other.material );
        else
          material = 0;

    }
   
    isect& operator =( const isect& other )
    {
        if( this != &other )
        {
            obj = other.obj;
            t = other.t;
            N = other.N;
            uvCoordinates = other.uvCoordinates;
//            material = other.material ? new Material( *(other.material) ) : 0;
			if( other.material )
            {
                if( material )
                    *material = *other.material;
                else
                    material = new Material(*other.material );
            }
            else
            {
                delete material;
                material = 0;
            }
        }
        return *this;
    }

public:
	bool outsideTheObject;
    const SceneObject 	*obj;
    double t;
    Vec3d N;
    Vec2d uvCoordinates;
    Material *material;         // if this intersection has its own material
                                // (as opposed to one in its associated object)
                                // as in the case where the material was interpolated

    const Material &getMaterial() const;
    // Other info here.
};

const double RAY_EPSILON = 0.00001;
const double NORMAL_EPSILON = 0.00001;

#endif // __RAY_H__
