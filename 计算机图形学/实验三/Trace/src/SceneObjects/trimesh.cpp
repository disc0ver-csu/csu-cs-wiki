#include <cmath>
#include <float.h>
#include "trimesh.h"

using namespace std;

Trimesh::~Trimesh()
{
	for( Materials::iterator i = materials.begin(); i != materials.end(); ++i )
		delete *i;
}

bool Trimesh::hasPerVertexNormals()
{
	return !(this->normals.empty());
}

// must add vertices, normals, and materials IN ORDER
void Trimesh::addVertex( const Vec3d &v )
{
    vertices.push_back( v );
}

void Trimesh::addMaterial( Material *m )
{
    materials.push_back( m );
}

void Trimesh::addNormal( const Vec3d &n )
{
    normals.push_back( n );
}

// Returns false if the vertices a,b,c don't all exist
bool Trimesh::addFace( int a, int b, int c )
{
    int vcnt = vertices.size();

    if( a >= vcnt || b >= vcnt || c >= vcnt )
        return false;

    TrimeshFace *newFace = new TrimeshFace( scene, new Material(*this->material), this, a, b, c );
    newFace->setTransform(this->transform);
    faces.push_back( newFace );
    scene->add(newFace);
    return true;
}

char *
Trimesh::doubleCheck()
// Check to make sure that if we have per-vertex materials or normals
// they are the right number.
{
    if( !materials.empty() && materials.size() != vertices.size() )
        return "Bad Trimesh: Wrong number of materials.";
    if( !normals.empty() && normals.size() != vertices.size() )
        return "Bad Trimesh: Wrong number of normals.";

    return 0;
}

// Calculates and returns the normal of the triangle too.
bool TrimeshFace::intersectLocal(const ray& r, isect& i) const
{
	// YOUR CODE HERE:
	// Add triangle intersection code here.
	// it currently ignores all triangles and just return false.
	//
	// Note that you are only intersecting a single triangle, and the vertices
	// of the triangle are supplied to you by the trimesh class.
	//
	// You should retrieve the vertices using code like this:
	//
	// const Vec3d& a = parent->vertices[ids[0]];
	// const Vec3d& b = parent->vertices[ids[1]];
	// const Vec3d& c = parent->vertices[ids[2]];

	//const Vec3d& a = parent->vertices[ids[0]];
	//const Vec3d& b = parent->vertices[ids[1]];
	//const Vec3d& c = parent->vertices[ids[2]];

	//Vec3d edge1 = b - a;
	//Vec3d edge2 = c - a;
	//// 计算平面法向量
	//Vec3d nor = edge1 ^ edge2;
	//nor.normalize();

	//// 判断是否与平面平行
	//float x = nor * r.getDirection();
	//if (!(x < 0.0))
	//	return false;
	//// Ax + By + Cz = d
	//float d = nor * a;
	//float t = (d - nor * r.getPosition()) / x;
	//if (t <= RAY_EPSILON)
	//	return false;
	//Vec3d intersection_point = r.at(t);
	//Vec3d edge3 = intersection_point - a;
	//// 同向法判断是否在平面内
	//if (((b - a) ^ (intersection_point - a)) * nor <= 0)
	//	return false;
	//else if (((c - b) ^ (intersection_point - b)) * nor <= 0)
	//	return false;
	//else if (((a - c) ^ (intersection_point - c)) * nor <= 0)
	//	return false;
	//else {
	//	//交点设置
	//	i.obj = this;
	//	i.setT(t);
	//	i.setN(nor);
	//	return true;
	//}
	const Vec3d& a = parent->vertices[ids[0]];
	const Vec3d& b = parent->vertices[ids[1]];
	const Vec3d& c = parent->vertices[ids[2]];


	Vec3d n = (b - a) ^ (c - a);
	if (n.length() != 0)	n.normalize();
	else return false;

	const Vec3d& pos = r.getPosition();
	const Vec3d& dir = r.getDirection();


	if (fabs(n*dir) < RAY_EPSILON)	return false;

	double d = n * a;
	double t = (d - n * pos) / (n * dir);

	const Vec3d& Q = r.at(t);
	if (((b - a) ^ (Q - a)) * n < 0 || ((c - b) ^ (Q - b)) * n < 0 || ((a - c) ^ (Q - c)) * n < 0)	
		return false;

	if (t < RAY_EPSILON)	
		return false;

	double alpha = ((c - b) ^ (Q - b))*n / (((b - a) ^ (c - a))*n);
	double beta = ((a - c) ^ (Q - c))*n / (((b - a) ^ (c - a))*n);
	double gamma = ((b - a) ^ (Q - a))*n / (((b - a) ^ (c - a))*n);

	if (parent->materials.size() > 0) {
		Material m = alpha * *parent->materials[ids[0]];
		m += beta * *parent->materials[ids[1]];
		m += gamma * *parent->materials[ids[2]];
		i.setMaterial(m);
	}

	if (TrimeshFace::parent->hasPerVertexNormals()) {
		vector<Vec3d> normals = TrimeshFace::parent->normals;
		Vec3d tmp = alpha * normals[ids[0]] + beta * normals[ids[1]] + gamma * normals[ids[2]];
		if (tmp.length() != 0)	tmp.normalize();
		i.setN(tmp);
	}
	else {
		i.setN(n);
	}

	i.setObject(this);
	i.setT(t);
	return true;
}


void
Trimesh::generateNormals()
// Once you've loaded all the verts and faces, we can generate per
// vertex normals by averaging the normals of the neighboring faces.
{
    int cnt = vertices.size();
    normals.resize( cnt );
    int *numFaces = new int[ cnt ]; // the number of faces assoc. with each vertex
    memset( numFaces, 0, sizeof(int)*cnt );
    
    for( Faces::iterator fi = faces.begin(); fi != faces.end(); ++fi )
    {
        Vec3d a = vertices[(**fi)[0]];
        Vec3d b = vertices[(**fi)[1]];
        Vec3d c = vertices[(**fi)[2]];
        
        Vec3d faceNormal = ((b-a) ^ (c-a));
		faceNormal.normalize();
        
        for( int i = 0; i < 3; ++i )
        {
            normals[(**fi)[i]] += faceNormal;
            ++numFaces[(**fi)[i]];
        }
    }

    for( int i = 0; i < cnt; ++i )
    {
        if( numFaces[i] )
            normals[i]  /= numFaces[i];
    }

    delete [] numFaces;
}

