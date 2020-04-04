#ifndef TRIMESH_H__
#define TRIMESH_H__

#include <list>
#include <vector>

#include "../scene/ray.h"
#include "../scene/material.h"
#include "../scene/scene.h"
class TrimeshFace;

class Trimesh : public MaterialSceneObject
{
    friend class TrimeshFace;
    typedef std::vector<Vec3d> Normals;
    typedef std::vector<Vec3d> Vertices;
    typedef std::vector<TrimeshFace*> Faces;
    typedef std::vector<Material*> Materials;
    Vertices vertices;
    Faces faces;
    Normals normals;
    Materials materials;
public:
    Trimesh( Scene *scene, Material *mat, TransformNode *transform )
        : MaterialSceneObject(scene, mat), 
			displayListWithMaterials(0),
			displayListWithoutMaterials(0)
    {
        this->transform = transform;
    }

	bool intersectLocal(const ray&r, isect&i) const { return false; } 

    ~Trimesh();
    
    // must add vertices, normals, and materials IN ORDER
    void addVertex( const Vec3d & );
    void addMaterial( Material *m );
    void addNormal( const Vec3d & );

    bool addFace( int a, int b, int c );

    char *doubleCheck();
    
    void generateNormals();

protected:
	void glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const;

	mutable int displayListWithMaterials;
	mutable int displayListWithoutMaterials;
};

class TrimeshFace : public MaterialSceneObject
{
    Trimesh *parent;
    int ids[3];
public:
    TrimeshFace( Scene *scene, Material *mat, Trimesh *parent, int a, int b, int c)
        : MaterialSceneObject( scene, mat )
    {
        this->parent = parent;
        ids[0] = a;
        ids[1] = b;
        ids[2] = c;
    }

    int operator[]( int i ) const
    {
        return ids[i];
    }

    virtual bool intersectLocal( const ray& r, isect& i ) const;

    virtual bool hasBoundingBoxCapability() const { return true; }
      
    virtual BoundingBox ComputeLocalBoundingBox()
    {
        BoundingBox localbounds;
        localbounds.max = maximum( parent->vertices[ids[0]], parent->vertices[ids[1]]);
		localbounds.min = minimum( parent->vertices[ids[0]], parent->vertices[ids[1]]);
        
        localbounds.max = maximum( parent->vertices[ids[2]], localbounds.max);
		localbounds.min = minimum( parent->vertices[ids[2]], localbounds.min);
        return localbounds;
    }
 };


#endif // TRIMESH_H__
