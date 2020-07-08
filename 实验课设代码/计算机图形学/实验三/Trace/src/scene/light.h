#ifndef __LIGHT_H__
#define __LIGHT_H__

#ifndef _WIN32
#include <algorithm>
using std::min;
using std::max;
#endif

#include "scene.h"

class Light
	: public SceneElement
{
public:
	virtual Vec3d shadowAttenuation(const Vec3d& P) const = 0;
	virtual double distanceAttenuation( const Vec3d& P ) const = 0;
	virtual Vec3d getColor( const Vec3d& P ) const = 0;
	virtual Vec3d getDirection( const Vec3d& P ) const = 0;

protected:
	Light( Scene *scene, const Vec3d& col )
		: SceneElement( scene ), color( col ) {}

	Vec3d 		color;

public:
	virtual void glDraw(GLenum lightID) const { }
	virtual void glDraw() const { }
};

class DirectionalLight
	: public Light
{
public:
	DirectionalLight( Scene *scene, const Vec3d& orien, const Vec3d& color )
		: Light( scene, color ), orientation( orien ) { orientation.normalize(); }
	virtual Vec3d shadowAttenuation(const Vec3d& P) const;
	virtual double distanceAttenuation( const Vec3d& P ) const;
	virtual Vec3d getColor( const Vec3d& P ) const;
	virtual Vec3d getDirection( const Vec3d& P ) const;

protected:
	Vec3d 		orientation;

public:
	void glDraw(GLenum lightID) const;
	void glDraw() const;
};

class PointLight
	: public Light
{
public:
	PointLight( Scene *scene, const Vec3d& pos, const Vec3d& color,
		float constantAttenuationTerm, float linearAttenuationTerm,
		float quadraticAttenuationTerm )
		: Light( scene, color ), position( pos ),
		constantTerm(constantAttenuationTerm), 
		linearTerm(linearAttenuationTerm),
		quadraticTerm(quadraticAttenuationTerm) 
		{}

	virtual Vec3d shadowAttenuation(const Vec3d& P) const;
	virtual double distanceAttenuation( const Vec3d& P ) const;
	virtual Vec3d getColor( const Vec3d& P ) const;
	virtual Vec3d getDirection( const Vec3d& P ) const;

	void setAttenuationConstants( float a, float b, float c )
	{
		constantTerm = a;
		linearTerm = b;
		quadraticTerm = c;
	}

protected:
	Vec3d position;

	// These three values are the a, b, and c in the distance
	// attenuation function (from the slide labelled 
	// "Intensity drop-off with distance"):
	//    f(d) = min( 1, 1/( a + b d + c d^2 ) )
	float constantTerm;		// a
	float linearTerm;		// b
	float quadraticTerm;	// c

public:
	void glDraw(GLenum lightID) const;
	void glDraw() const;

protected:
};

#endif // __LIGHT_H__
