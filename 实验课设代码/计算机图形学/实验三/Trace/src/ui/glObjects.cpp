#pragma warning (disable: 4786)

#include "gl.h"
#include "gl.h"
#include "glu.h"

#include "../vecmath/mat.h"

#include "../scene/scene.h"
#include "../scene/ray.h"
#include "../scene/light.h"

#include "../SceneObjects/Box.h"
#include "../SceneObjects/Cone.h"
#include "../SceneObjects/Cylinder.h"
#include "../SceneObjects/Sphere.h"
#include "../SceneObjects/Square.h"
#include "../SceneObjects/trimesh.h"

using namespace std;

const double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;

void Scene::glDraw(int quality, bool actualMaterials, bool actualTextures) const
{
	typedef vector<Geometry*>::const_iterator iter;

	// try the non-bounded objects
	for( iter j = objects.begin(); j != objects.end(); ++j )
	{
		(*j)->glDraw(quality, actualMaterials, actualTextures);
	}
}



void Geometry::glDraw(int quality, bool actualMaterials, bool actualTextures) const
{
	glPushMatrix();
	{
		Mat4d colMajor = transform->transform().transpose();
		glMultMatrixd( colMajor.n );
		glDrawLocal(quality, actualMaterials, actualTextures);
	}
	glPopMatrix();
}

void setMaterialProperty( GLenum property, Vec3d value )
{
	GLfloat val[4];
	val[0] = GLfloat(value[0]);
	val[1] = GLfloat(value[1]);
	val[2] = GLfloat(value[2]);
	val[3] = 1.0; // alpha
	glMaterialfv( GL_FRONT_AND_BACK, property, val );
}

void setGLMaterial( const Material& mat, const SceneObject* object )
{
	// Setup material parameters
	isect i;
	i.setObject(object);
	setMaterialProperty( GL_AMBIENT, mat.ka(i) );
	setMaterialProperty( GL_DIFFUSE, mat.kd(i) );
	setMaterialProperty( GL_SPECULAR, mat.ks(i) );
	setMaterialProperty( GL_EMISSION, mat.ke(i) );
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, mat.shininess(i) );
}

void SceneObject::glDraw(int quality, bool actualMaterials, bool actualTextures) const
{
	glPushMatrix();
	{
		Mat4d colMajor = transform->transform().transpose();
		glMultMatrixd( colMajor.n );

		if( actualMaterials )
		{
			setGLMaterial( getMaterial(), this );
		}

		// Now draw the object in its local coordinate frame
		glDrawLocal(quality, actualMaterials, actualTextures);
	}
	glPopMatrix();
}

void Sphere::glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const
{
	// Use this for display lists
	static std::map<int, GLuint> displayLists;

	std::map<int, GLuint>::iterator dispListItr = displayLists.find( quality );
	if( dispListItr == displayLists.end() )
	{
		dispListItr = (displayLists.insert( std::make_pair(quality, glGenLists(1)) )).first;
		glNewList(dispListItr->second, GL_COMPILE);

		const int divisions = quality;
		GLUquadricObj* gluq;

		gluq = gluNewQuadric();
		gluQuadricDrawStyle( gluq, GLU_FILL );
		gluQuadricTexture( gluq, GL_TRUE );
		gluSphere(gluq, 1.0, divisions, divisions);
		gluDeleteQuadric( gluq );

		glEndList();
	}

	glCallList(dispListItr->second);
}

void drawTesselatedSquare(int quality)
{
	glPushMatrix();
		glTranslated( -0.5, -0.5, 0 );

		for( int j=0; j < quality; j++ )
		{
			glBegin( GL_QUAD_STRIP );
			for( int i=0; i <= quality; i++ )
			{
				glNormal3d( 0.0, 0.0, 1.0 );
				glVertex3d( 
					double(i)/double(quality), 
					double(j)/double(quality),
					0.0 );
				glNormal3d( 0.0, 0.0, 1.0 );
				glVertex3d( 
					double(i)/double(quality), 
					double(j+1)/double(quality),
					0.0 );
			}
			glEnd();
		}
	glPopMatrix();
}

void Box::glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const
{
	// Use this for display lists
	static std::map<int, GLuint> boxDisplayLists;

	std::map<int, GLuint>::iterator dispListItr = boxDisplayLists.find( quality );
	if( dispListItr == boxDisplayLists.end() )
	{
		dispListItr = (boxDisplayLists.insert( std::make_pair(quality, glGenLists(1)) )).first;
		glNewList(dispListItr->second, GL_COMPILE);

		// We need to tesselate boxes or lighting attenuation won't show up
		// properly.

		glPushMatrix();
			glTranslated( 0, 0, 0.5 );
			drawTesselatedSquare( quality );
		glPopMatrix();

		glPushMatrix();
			glTranslated( 0, 0, -0.5 );
			glRotated(180.0, 1.0, 0.0, 0.0);
			drawTesselatedSquare( quality );
		glPopMatrix();

		glPushMatrix();
			glTranslated( 0, 0.5, 0.0 );
			glRotated(-90.0, 1.0, 0.0, 0.0);
			drawTesselatedSquare( quality );
		glPopMatrix();

		glPushMatrix();
			glTranslated( 0, -0.5, 0.0 );
			glRotated(90.0, 1.0, 0.0, 0.0);
			drawTesselatedSquare( quality );
		glPopMatrix();

		glPushMatrix();
			glTranslated( 0.5, 0, 0.0 );
			glRotated(90.0, 0.0, 1.0, 0.0);
			drawTesselatedSquare( quality );
		glPopMatrix();

		glPushMatrix();
			glTranslated( -0.5, 0, 0.0 );
			glRotated(-90.0, 0.0, 1.0, 0.0);
			drawTesselatedSquare( quality );
		glPopMatrix();

		glEndList();
	}

	glCallList(dispListItr->second);
}



void Cone::glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const
{
	const double r1 = b_radius;
	const double r2 = t_radius;
	const double h = height;
	const int divisions = quality;

	GLUquadricObj* gluq;

	/* GLU will again do the work.  draw the sides of the cylinder. */
	gluq = gluNewQuadric();
	gluQuadricDrawStyle( gluq, GLU_FILL );
	gluQuadricTexture( gluq, GL_TRUE );
	gluCylinder( gluq, r1, r2, h, divisions, divisions);
	gluDeleteQuadric( gluq );

	if( capped )
	{
		if ( r1 > 0.0 )
		{
		/* if the r1 end does not come to a point, draw a flat disk to
			cover it up. */
    
			gluq = gluNewQuadric();
			gluQuadricDrawStyle( gluq, GLU_FILL );
			gluQuadricTexture( gluq, GL_TRUE );
			gluQuadricOrientation( gluq, GLU_INSIDE );
			gluDisk( gluq, 0.0, r1, divisions, divisions);
			gluDeleteQuadric( gluq );
		}

		if ( r2 > 0.0 )
		{
		/* if the r2 end does not come to a point, draw a flat disk to
			cover it up. */
    
			/* save the current matrix mode. */	
			int savemode;
			glGetIntegerv( GL_MATRIX_MODE, &savemode );
    
			/* translate the origin to the other end of the cylinder. */
			glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glTranslated( 0.0, 0.0, h );
    
			/* draw a disk centered at the new origin. */
			gluq = gluNewQuadric();
			gluQuadricDrawStyle( gluq, GLU_FILL );
			gluQuadricTexture( gluq, GL_TRUE );
			gluQuadricOrientation( gluq, GLU_OUTSIDE );
			gluDisk( gluq, 0.0, r2, divisions, divisions);
			gluDeleteQuadric( gluq );
    
			/* restore the matrix stack and mode. */
			glPopMatrix();
			glMatrixMode( savemode );
		}
	}
}

void Cylinder::glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const
{
	// Use this for display lists
	static std::map<int, GLuint> displayLists;

	std::map<int, GLuint>::iterator dispListItr = displayLists.find( quality );
	if( dispListItr == displayLists.end() )
	{
		dispListItr = (displayLists.insert( std::make_pair(quality, glGenLists(1)) )).first;
		glNewList(dispListItr->second, GL_COMPILE);

		const int divisions = quality;
		const double r1 = 1.0, r2 = 1.0;
		const double h = 1.0;

		GLUquadricObj* gluq;
    
		/* GLU will again do the work.  draw the sides of the cylinder. */
		gluq = gluNewQuadric();
		gluQuadricDrawStyle( gluq, GLU_FILL );
		gluQuadricTexture( gluq, GL_TRUE );
		gluCylinder( gluq, r1, r2, h, divisions, divisions);
		gluDeleteQuadric( gluq );
    
		if ( capped )
		{
			gluq = gluNewQuadric();
			gluQuadricDrawStyle( gluq, GLU_FILL );
			gluQuadricTexture( gluq, GL_TRUE );
			gluQuadricOrientation( gluq, GLU_INSIDE );
			gluDisk( gluq, 0.0, r1, divisions, divisions);
			gluDeleteQuadric( gluq );

			/* save the current matrix mode. */	
			int savemode;
			glGetIntegerv( GL_MATRIX_MODE, &savemode );
        
			/* translate the origin to the other end of the cylinder. */
			glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glTranslated( 0.0, 0.0, h );
        
			/* draw a disk centered at the new origin. */
			gluq = gluNewQuadric();
			gluQuadricDrawStyle( gluq, GLU_FILL );
			gluQuadricTexture( gluq, GL_TRUE );
			gluQuadricOrientation( gluq, GLU_OUTSIDE );
			gluDisk( gluq, 0.0, r2, divisions, divisions);
			gluDeleteQuadric( gluq );
        
			/* restore the matrix stack and mode. */
			glPopMatrix();
			glMatrixMode( savemode );
		}
		glEndList();
	}

	glCallList(dispListItr->second);
}


void Square::glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const
{
	// Use this for display lists
	static std::map<int, GLuint> displayLists;

	std::map<int, GLuint>::iterator dispListItr = displayLists.find( quality );
	if( dispListItr == displayLists.end() )
	{
		dispListItr = (displayLists.insert( std::make_pair(quality, glGenLists(1)) )).first;
		glNewList(dispListItr->second, GL_COMPILE);

		drawTesselatedSquare( quality );

		glEndList();
	}

	glCallList(dispListItr->second);
}


void Trimesh::glDrawLocal(int quality, bool actualMaterials, bool actualTextures) const
{
	// Could be doing this a lot more efficiently w/ vertex arrays, but that
	// would involve changing the data storage method just for debugging purposes
	// which is probably wrong.

	int* d;
	if( actualMaterials )
		d = &displayListWithMaterials;
	else
		d = &displayListWithoutMaterials;
	int& displayList = *d;

	// We'll try to buy some time back by using display lists.
	if( displayList == 0 )
	{
		displayList = glGenLists(1);
		glNewList( displayList, GL_COMPILE );

		glBegin( GL_TRIANGLES );
		for( Faces::const_iterator itr = faces.begin(); itr != faces.end(); ++itr )
		{
			const int vert1 = (*(*itr))[0];
			const int vert2 = (*(*itr))[1];
			const int vert3 = (*(*itr))[2];

			if( normals.empty() )
			{
				const Vec3d& a = vertices[vert1];
				const Vec3d& b = vertices[vert2];
				const Vec3d& c = vertices[vert3];

				Vec3d cv=(b - a) ^ (c - a);

				// there exists some bad triangles such that two vertices coincide
				// check this before normalize
				if (!cv.iszero())
					glNormal3dv( cv.getPointer() );
			}

			if( ! normals.empty() )
				glNormal3dv( normals[vert1].getPointer() );
			if( !materials.empty() && actualMaterials )
				setGLMaterial( *materials[vert1], *itr );
			glVertex3dv( vertices[vert1].getPointer() );

			if( ! normals.empty() )
				glNormal3dv( normals[vert2].getPointer() );
			if( !materials.empty() && actualMaterials )
				setGLMaterial( *materials[vert2], *itr );
			glVertex3dv( vertices[vert2].getPointer() );

			if( ! normals.empty() )
				glNormal3dv( normals[vert3].getPointer() );
			if( !materials.empty() && actualMaterials )
				setGLMaterial( *materials[vert3], *itr );
			glVertex3dv( vertices[vert3].getPointer() );
		}
		glEnd();

		glEndList();
	}

	glCallList(displayList);
}

void PointLight::glDraw(GLenum lightID) const
{

	GLfloat pos[4];
	pos[0] = GLfloat(position[0]);
	pos[1] = GLfloat(position[1]);
	pos[2] = GLfloat(position[2]);
	pos[3] = 1.0f;
	glLightfv( lightID, GL_POSITION, pos );

	GLfloat fColor[4];
	fColor[0] = GLfloat(color[0]);
	fColor[1] = GLfloat(color[1]);
	fColor[2] = GLfloat(color[2]);
	fColor[3] = 1.0f;
	glLightfv( lightID, GL_DIFFUSE, fColor );
	glLightfv( lightID, GL_SPECULAR, fColor );

	glLightf( lightID, GL_CONSTANT_ATTENUATION, constantTerm );
	glLightf( lightID, GL_LINEAR_ATTENUATION, linearTerm );
	glLightf( lightID, GL_QUADRATIC_ATTENUATION, quadraticTerm );
}

void PointLight::glDraw() const
{
	GLfloat fColor[4];
	fColor[0] = GLfloat(color[0]);
	fColor[1] = GLfloat(color[1]);
	fColor[2] = GLfloat(color[2]);
	fColor[3] = 1.0f;

	// We'll use this snippet of code to make it a billboard.
	float modelview[16];
	int i,j;

	glPushMatrix();
		// Move to the correct light position
		glTranslated( position[0], position[1], position[2] );

		// get the current modelview matrix
		glGetFloatv(GL_MODELVIEW_MATRIX , modelview);

		// undo all rotations/scales
		for( i=0; i<3; i++ ) 
			for( j=0; j<3; j++ ) {
				if ( i==j )
					modelview[i*4+j] = 1.0;
				else
					modelview[i*4+j] = 0.0;
			}

		// set the modelview with no rotations and scaling
		glLoadMatrixf(modelview);
		glScaled( 0.1, 0.1, 0.1 );

		// Now, draw the light.  It will be a neat little circle
		// with lines emanating
		glDisable( GL_LIGHTING );
		glColor3fv( fColor );

		{
			static GLuint displayList = 0;
			if( displayList == 0 )
			{
				displayList = glGenLists(1);
				glNewList( displayList, GL_COMPILE );

				glBegin( GL_LINE_STRIP );
				{
					const int circlePoints = 24;
					for( i=0; i <= circlePoints; i++ )
					{
						const double angle = (double(i)/double(circlePoints))*(2.0*pi);
						glVertex3d( cos(angle), sin(angle), 0.0 );
					}
				}
				glEnd();

				glBegin( GL_LINES );
				{
					const int numLines = 8;
					for( i=0; i < numLines; i++ )
					{
						const double angle = (double(i)/double(numLines))*(2.0*pi);
						glVertex3d( 1.3*cos(angle), 1.3*sin(angle), 0.0 );
						glVertex3d( 2.0*cos(angle), 2.0*sin(angle), 0.0 );
					}
				}
				glEnd();

				glEndList();
			}
		
			glCallList(displayList);
		}

		glEnable( GL_LIGHTING );

	// restores the modelview matrix
	glPopMatrix();
}

void DirectionalLight::glDraw(GLenum lightID) const
{
	GLfloat fColor[4];
	fColor[0] = GLfloat(color[0]);
	fColor[1] = GLfloat(color[1]);
	fColor[2] = GLfloat(color[2]);
	fColor[3] = 1.0f;
	glLightfv( lightID, GL_DIFFUSE, fColor );
	glLightfv( lightID, GL_SPECULAR, fColor );

	GLfloat pos[4];
	pos[0] = GLfloat(-orientation[0]);
	pos[1] = GLfloat(-orientation[1]);
	pos[2] = GLfloat(-orientation[2]);
	pos[3] = 0.0f;
	glLightfv( lightID, GL_POSITION, pos );

	glLightf( lightID, GL_CONSTANT_ATTENUATION, 1.0f );
	glLightf( lightID, GL_LINEAR_ATTENUATION, 0.0f );
	glLightf( lightID, GL_QUADRATIC_ATTENUATION, 0.0f );
}

void arrow()
{
	glPushMatrix();
		glTranslated( -1.5, 0.0, 0.0 );
		glBegin( GL_LINE_STRIP );
			glVertex3d( 0.0, 0.0, 0.0 );
			glVertex3d( 1.0, 0.0, 0.0 );
			glVertex3d( 1.0, 0.2, 0.0 );
			glVertex3d( 1.5, 0.0, 0.0 );
			glVertex3d( 1.0, -0.2, 0.0 );
			glVertex3d( 1.0, 0.0, 0.0 );
		glEnd();
	glPopMatrix();
}

void DirectionalLight::glDraw() const
{
	GLfloat fColor[4];
	fColor[0] = GLfloat(color[0]);
	fColor[1] = GLfloat(color[1]);
	fColor[2] = GLfloat(color[2]);
	fColor[3] = 1.0f;

	glPushMatrix();

		double maxDist;

		// We essentially want to find the spherical bounding volume for
		// the scene so we can put our directional lights just outside it.
		Vec3d maxVec = maximum( scene->bounds().max, scene->bounds().min );
		maxVec = maximum( scene->getCamera().getEye(), maxVec );
		maxVec = maximum( scene->getCamera().getEye() + scene->getCamera().getLook(), maxVec );
		maxDist = max( max( maxVec[0], maxVec[1] ), maxVec[2] );

		Vec3d uAxis = orientation;
		uAxis.normalize();

		// The first thing we need is the light's coordinate system (u,v,w).  To do this,
		// we will cross the light's orientation vector with the three coordinate
		// axes and find the 'best conditioned' one -- that is, the cross product
		// with the largest length (so we can normalize it w/o numerical error).
		Vec3d vAxis = uAxis ^ Vec3d(1.0,0.0,0.0);
		{
			Vec3d test = uAxis ^ Vec3d(0.0,1.0,0.0);
			if( test.length2() > vAxis.length2() )
				vAxis = test;

			test = uAxis ^ Vec3d(0.0,0.0,1.0);
			if( test.length2() > vAxis.length2() )
				vAxis = test;
		}
		vAxis.normalize();

		Vec3d wAxis = uAxis ^ vAxis;
		wAxis.normalize();

		// Now, we have a coordinate system.  We want to rotate our coordinate
		// system to line up with this one. To do this, we place the three vectors
		// in a matrix -- transposed (because this is the same as inverse for
		// an orthonormal basis).
		{
			GLdouble rotMat[16];
			rotMat[0] = uAxis[0];
			rotMat[1] = uAxis[1];
			rotMat[2] = uAxis[2];
			rotMat[3] = 0.0;
			rotMat[4] = vAxis[0];
			rotMat[5] = vAxis[1];
			rotMat[6] = vAxis[2];
			rotMat[7] = 0.0;
			rotMat[8] = wAxis[0];
			rotMat[9] = wAxis[1];
			rotMat[10] = wAxis[2];
			rotMat[11] = 0.0;
			rotMat[12] = 0.0;
			rotMat[13] = 0.0;
			rotMat[14] = 0.0;
			rotMat[15] = 1.0;
			glMultMatrixd( rotMat );
		}

		glScaled( maxDist, maxDist, maxDist );
		glTranslated( -1.3, 0.0, 0.0 );
		
		glScaled( 0.2, 0.2, 0.2 );

		// Now, draw the light.  It will be a group of arrows.
		glDisable( GL_LIGHTING );
		glColor3fv( fColor );

		glPushMatrix();
			glTranslated( 0.0, 0.0, 0.5 );
			arrow();
		glPopMatrix();

		glPushMatrix();
			glRotated( 90.0, 1.0, 0.0, 0.0 );
			glTranslated( 0.0, 0.0, 0.5 );
			arrow();
		glPopMatrix();

		glPushMatrix();
			glRotated( 180.0, 1.0, 0.0, 0.0 );
			glTranslated( 0.0, 0.0, 0.5 );
			arrow();
		glPopMatrix();

		glPushMatrix();
			glRotated( 270.0, 1.0, 0.0, 0.0 );
			glTranslated( 0.0, 0.0, 0.5 );
			arrow();
		glPopMatrix();

		glEnable( GL_LIGHTING );
	glPopMatrix();

}

