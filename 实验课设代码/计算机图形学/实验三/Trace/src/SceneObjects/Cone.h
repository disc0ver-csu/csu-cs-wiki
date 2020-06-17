#ifndef __CONE_H__
#define __CONE_H__

#include "../scene/scene.h"

class Cone
	: public MaterialSceneObject
{
public:
	Cone( Scene *scene, Material *mat, 
			double h = 1.0, double br = 1.0, double tr = 0.0, 
			bool cap = false )
		: MaterialSceneObject( scene, mat )
	{
		height = h;
		b_radius = (br < 0.0f)?(-br):(br);
		t_radius = (tr < 0.0f)?(-tr):(tr);
		capped = cap;

		if(b_radius < 0.0001) b_radius = 0.0001;
		if(t_radius < 0.0001) t_radius = 0.0001;

		beta = (t_radius - b_radius)/height;

		// Use the right radius
		if(fabs(beta) < 0.001) beta = 0.001;

		if(beta < 0.0) gamma = t_radius / beta;
		else gamma = b_radius / beta;

		beta_squared = beta * beta;

		// For the under the origin wierdness
		if(gamma < 0.0) gamma = gamma - height;
		gamma_squared = gamma * gamma;

	}

	virtual bool intersectLocal( const ray& r, isect& i ) const;
	virtual bool hasBoundingBoxCapability() const { return true; }

    virtual BoundingBox ComputeLocalBoundingBox()
    {
        BoundingBox localbounds;
		double biggest_radius = (b_radius > t_radius)?(b_radius):(t_radius);

		localbounds.min = Vec3d(-biggest_radius, -biggest_radius, (height < 0.0f)?(height):(0.0f));
		localbounds.max = Vec3d(biggest_radius, biggest_radius, (height < 0.0f)?(0.0f):(height));
        return localbounds;
    }

	bool intersectBody( const ray& r, isect& i ) const;
	bool intersectCaps( const ray& r, isect& i ) const;

protected:
	bool isGoodRoot(Vec3d root) const;
	double radiusAt(double h) const;
    
	bool capped;
	double height;
	double b_radius;
	double t_radius;

	double beta, beta_squared;
	double gamma, gamma_squared;

protected:
	void glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const;

};

#endif // __CONE_H__
