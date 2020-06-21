#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include "../scene/scene.h"

class Cylinder
	: public MaterialSceneObject
{
public:
	Cylinder( Scene *scene, Material *mat )
		: MaterialSceneObject( scene, mat ), capped( true )
	{
	}

	virtual bool intersectLocal( const ray& r, isect& i ) const;
	virtual bool hasBoundingBoxCapability() const { return true; }

    virtual BoundingBox ComputeLocalBoundingBox()
    {
        BoundingBox localbounds;
		localbounds.min = Vec3d(-1.0f, -1.0f, 0.0f);
		localbounds.max = Vec3d(1.0f, 1.0f, 1.0f);
        return localbounds;
    }

    bool intersectBody( const ray& r, isect& i ) const;
	bool intersectCaps( const ray& r, isect& i ) const;

protected:
	bool capped;

protected:
	void glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const;

};

#endif // __CYLINDER_H__
