#pragma warning (disable: 4786)

#include "debuggingView.h"
#include "ModelerCamera.h"
#include "../RayTracer.h"
#include "../scene/scene.h"
#include "../scene/light.h"

// We include these files from modeler so that we can
// display the rendered image in OpenGL -- for debugging
// purposes.


#include "Fl.H"
#include "Fl_Gl_Window.H"
#include "gl.h"
#include "glu.h"
#include <cstdio>

static const int	kMouseRotationButton			= FL_LEFT_MOUSE;
static const int	kMouseTranslationButton			= FL_MIDDLE_MOUSE;
static const int	kMouseZoomButton				= FL_RIGHT_MOUSE;


// Helper functions from the red book so we can print text on the
// screen.
GLubyte space[] =
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
GLubyte letters[][13] = {
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
    {0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
    {0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
    {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
};

GLuint fontOffset;

void makeRasterFont(void)
{
   GLuint i, j;
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   fontOffset = glGenLists (128);
   for (i = 0,j = 'A'; i < 26; i++,j++) {
      glNewList(fontOffset + j, GL_COMPILE);
      glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
      glEndList();
   }
   glNewList(fontOffset + ' ', GL_COMPILE);
   glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
   glEndList();
}

void printString(char *s)
{
   static bool haveInitialized = false;
   if( !haveInitialized ) {
	   makeRasterFont();
	   haveInitialized = true;
   }
   glPushAttrib (GL_LIST_BIT);
   glListBase(fontOffset);
   glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
   glPopAttrib ();
}

	bool				m_showGeometry;
	bool				m_showLights;
	bool				m_showCamera;
	bool				m_showAxes;

	bool				m_showVisibilityRays;
	bool				m_showReflectionRays;
	bool				m_showRefractionRays;
	bool				m_showShadowRays;


DebuggingView::DebuggingView(int x, int y, int w, int h, char *label)
	: Fl_Gl_Window(x,y,w,h,label), raytracer(0),
	  m_shadingMode(NORMAL), m_quality(HIGH_QUALITY),
	  m_lightingMode(DEFAULT_LIGHTING),
	  m_useSceneMaterials(true),
	  m_useSceneTextures(true),
	  m_dirty(true),
	  m_showGeometry(true), m_showLights(true), 
	  m_showCamera(true), m_showAxes(true),
	  m_showNormals(true),
	  m_showVisibilityRays(true), m_showReflectionRays(true),
	  m_showRefractionRays(true), m_showShadowRays(false)
{
    m_camera = new ModelerCamera();
}

DebuggingView::~DebuggingView()
{
	delete m_camera;
}

int DebuggingView::handle(int event)
{
    unsigned eventCoordX = h() - Fl::event_x();
	unsigned eventCoordY = Fl::event_y();
	unsigned eventButton = Fl::event_button();
	unsigned eventState  = Fl::event_state();

	switch(event)	 
	{
	case FL_PUSH:
		{
			switch(eventButton)
			{
			case kMouseRotationButton:
				m_camera->clickMouse(kActionRotate, eventCoordX, eventCoordY );
				break;
			case kMouseTranslationButton:
				m_camera->clickMouse(kActionTranslate, eventCoordX, eventCoordY );
				break;
			case kMouseZoomButton:
				m_camera->clickMouse(kActionZoom, eventCoordX, eventCoordY );
				break;
			}
           // printf("push %d %d\n", eventCoordX, eventCoordY);
		}
		break;
	case FL_DRAG:
		{
			m_camera->dragMouse(eventCoordX, eventCoordY);
            //printf("drag %d %d\n", eventCoordX, eventCoordY);
		}
		break;
	case FL_RELEASE:
		{
			switch(eventButton)
			{
			case kMouseRotationButton:
			case kMouseTranslationButton:
			case kMouseZoomButton:
				m_camera->releaseMouse(eventCoordX, eventCoordY );
				break;
			}
          //  printf("release %d %d\n", eventCoordX, eventCoordY);
		}
		break;
	default:
		return 0;
	}
	
	redraw();

	return 1;
}

void DebuggingView::resetCamera()
{
	const Camera& sceneCamera = raytracer->getScene().getCamera();
	m_camera->reset();

	double maxDist;

	const Scene& scene = raytracer->getScene();

	Vec3d maxVec = maximum( scene.bounds().max, scene.bounds().min );
	maxVec = maximum( scene.getCamera().getEye(), maxVec );
	maxVec = maximum( scene.getCamera().getEye() + scene.getCamera().getLook(), maxVec );
	maxDist = max( max( maxVec[0], maxVec[1] ), maxVec[2] );

	m_camera->setDolly( maxDist );
}


void checkGLError()
{
	GLenum error_flag; 
	error_flag = glGetError(); 
	if(error_flag != GL_NO_ERROR)
		printf("Error: %1s (%i) in %1s.\n",gluErrorString(error_flag),error_flag,"method name"); 
}


static GLfloat lightPosition0[] = { 4, 2, -4, 0 };
static GLfloat lightDiffuse0[]  = { 1,1,1,1 };
static GLfloat lightPosition1[] = { -2, 1, 5, 0 };
static GLfloat lightDiffuse1[]  = { 1, 1, 1, 1 };

void DebuggingView::draw()
{
    if (!valid())
    {
        glShadeModel( GL_SMOOTH );
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT0 );
        glEnable( GL_LIGHT1 );
		glEnable( GL_NORMALIZE );
    }

  	glViewport( 0, 0, w(), h() );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,-float(w())/float(h()),1.0,100.0);
				
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
	
	m_camera->applyViewingTransform();

	// Need to apply an extra transform so that our camera 'approximately'
	// lines up with the scene camera, initially, and to correct for our 
	// definition of "up."
	{
		Vec3d uAxis = raytracer->getScene().getCamera().getU();
		Vec3d vAxis = raytracer->getScene().getCamera().getV();
		Vec3d wAxis = uAxis ^ vAxis;
		uAxis = wAxis ^ vAxis;

		uAxis.normalize();
		vAxis.normalize();
		wAxis.normalize();

		GLdouble rotMat[16];
		rotMat[0] = uAxis[0];
		rotMat[1] = vAxis[0];
		rotMat[2] = wAxis[0];
		rotMat[3] = 0.0;
		rotMat[4] = uAxis[1];
		rotMat[5] = vAxis[1];
		rotMat[6] = wAxis[1];
		rotMat[7] = 0.0;
		rotMat[8] = uAxis[2];
		rotMat[9] = vAxis[2];
		rotMat[10] = wAxis[2];
		rotMat[11] = 0.0;
		rotMat[12] = 0.0;
		rotMat[13] = 0.0;
		rotMat[14] = 0.0;
		rotMat[15] = 1.0;

		glMultMatrixd( rotMat );
	}
	

	if( m_showAxes )
		drawAxes();

	if( raytracer == 0 || !raytracer->sceneLoaded() )
		return;

	if( m_showLights )
		drawLights();

	if( m_showGeometry )
	{
		lightScene();
		drawScene();
	}

	drawRays();

	if( m_showCamera )
		drawCamera();
}

void DebuggingView::setRayTracer(RayTracer *tracer)
{
	raytracer = tracer;
}


void DebuggingView::drawAxes()
{
	// Draw the origin
	glShadeModel(GL_FLAT);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		// x axis
		glColor3f(1.0, 0.0, 0.0);
		glVertex3d( 0.0, 0.0, 0.0 );
		glVertex3d( 1.0, 0.0, 0.0 );

		// y axis
		glColor3f(0.0, 1.0, 0.0);
		glVertex3d( 0.0, 0.0, 0.0 );
		glVertex3d( 0.0, 1.0, 0.0 );

		// z axis
		glColor3f(0.0, 0.0, 1.0);
		glVertex3d( 0.0, 0.0, 0.0 );
		glVertex3d( 0.0, 0.0, 1.0 );
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos3f(1.2f, 0.0f, 0.0f);
	printString("X");

	glColor3f(0.0, 1, 0.0);
	glRasterPos3f(0.0f, 1.2f, 0.0f);
	printString("Y");

	glColor3f(0.0f, 0.0f, 1.0f);
	glRasterPos3f(0.0f, 0.0f, 1.2f);
	printString("Z");

	glEnable(GL_LIGHTING);
}

void DebuggingView::lightScene()
{
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	static std::vector<GLenum> lights;
	if( lights.empty() )
	{
		lights.push_back( GL_LIGHT0 );
		lights.push_back( GL_LIGHT1 );
		lights.push_back( GL_LIGHT2 );
		lights.push_back( GL_LIGHT3 );
		lights.push_back( GL_LIGHT4 );
		lights.push_back( GL_LIGHT5 );
		lights.push_back( GL_LIGHT6 );
		lights.push_back( GL_LIGHT7 );
	}

	// Reset all the lights
	{
		GLfloat lightColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
		for( std::vector<GLenum>::const_iterator glLightsItr = lights.begin();
			glLightsItr != lights.end();
			++glLightsItr )
		{
			glLightfv( *glLightsItr, GL_DIFFUSE, lightColor );
			glLightfv( *glLightsItr, GL_SPECULAR, lightColor );
			glLightfv( *glLightsItr, GL_AMBIENT, lightColor );
		}
	}

	if( m_lightingMode == SCENE_LIGHTING )
	{
		std::vector<GLenum>::const_iterator glLightsItr = lights.begin();
		for (std::vector<Light*>::const_iterator l = raytracer->getScene().beginLights(); 
			l != raytracer->getScene().endLights(); ++l)
		{
			if(glLightsItr == lights.end())
				std::cerr << "Not displaying all lights in debugging mode; GL can only handle 8." 
					<< std::endl;

			(*l)->glDraw( *glLightsItr );
			++glLightsItr;
		}

		GLfloat ambient[4];
		ambient[0] = (raytracer->getScene().ambient())[0];
		ambient[1] = (raytracer->getScene().ambient())[1];
		ambient[2] = (raytracer->getScene().ambient())[2];
		ambient[3] = 1.0f;
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	}
	else
	{
		glLightfv( GL_LIGHT0, GL_POSITION, lightPosition0 );
		glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse0 );
		glLightfv( GL_LIGHT1, GL_POSITION, lightPosition1 );
		glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse1 );
	}
}

void DebuggingView::drawLights()
{
	for (std::vector<Light*>::const_iterator l = raytracer->getScene().beginLights(); 
		l != raytracer->getScene().endLights(); ++l)
		(*l)->glDraw();
}

void DebuggingView::drawScene()
{
	switch (m_shadingMode)
	{
	case NORMAL:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glShadeModel(GL_SMOOTH);
		break;
	case FLAT_SHADING:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glShadeModel(GL_FLAT);
		break;
	case WIREFRAME:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glShadeModel(GL_FLAT);
	default:
		break;
	}

	int divisions;
	switch(m_quality)
	{
        case HIGH_QUALITY: 
            divisions = 32; break;
        case MEDIUM_QUALITY: 
            divisions = 20; break;
        case LOW_QUALITY:
            divisions = 12; break;
        case POOR_QUALITY:
            divisions = 8; break;
	}

	// Set up default material parameters
	{

		GLfloat mat[4];
		mat[0] = 0.1f;
		mat[1] = 0.1f;
		mat[2] = 0.2f;
		mat[3] = 1.0f;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat );
	
		mat[0] = 0.4f;
		mat[1] = 0.4f;
		mat[2] = 0.8f;
		mat[3] = 1.0f;
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat );

		mat[0] = 0.0f;
		mat[1] = 0.0f;
		mat[2] = 0.0f;
		mat[3] = 1.0f;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat );
	}

	raytracer->getScene().glDraw(divisions, m_useSceneMaterials, 
		m_useSceneTextures);
}


void DebuggingView::drawRays()
{
	glDisable( GL_LIGHTING );
	// Now draw all the rays
	for( std::vector< std::pair<ray, isect> >::const_iterator rayItr = 
		raytracer->getScene().intersectCache.begin();
		rayItr != raytracer->getScene().intersectCache.end();
		++rayItr )
	{
		switch( rayItr->first.type() )
		{
		case ray::VISIBILITY:
			if( !m_showVisibilityRays ) continue;
			glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
			break;
			
		case ray::REFLECTION:
			if( !m_showReflectionRays ) continue;
			glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
			break;

		case ray::REFRACTION:
			if( !m_showRefractionRays ) continue;
			glColor4f( 1.0f, 1.0f, 0.0f, 1.0f );
			break;

		case ray::SHADOW:
			if( !m_showShadowRays ) continue;
			glColor4f( 0.20f, 0.45f, 0.72f, 1.0f );
			break;
		}
		Vec3d p = rayItr->first.getPosition();
		Vec3d d = rayItr->first.getDirection();
		Vec3d isectPoint = p + rayItr->second.t*d;

		glEnable( GL_LINE_STIPPLE );
		glLineStipple( 1, 0x3333 );

		glBegin( GL_LINES );
			glVertex3dv( p.getPointer() );
			glVertex3dv( isectPoint.getPointer() );
		glEnd();

		glDisable(GL_LINE_STIPPLE);

		if( m_showNormals )
		{
			glPushMatrix();
				glTranslatef( isectPoint[0], isectPoint[1], isectPoint[2] );
				glBegin( GL_LINES );
					glColor4f( 0.5f, 1.0f, 0.5f, 1.0f );
					glVertex3d( 0.0, 0.0, 0.0 );
					glVertex3dv( rayItr->second.N.getPointer() );
				glEnd();
			glPopMatrix();
		}
	}
	glEnd();
	glEnable( GL_LIGHTING );
}


void DebuggingView::drawCamera()
{
	glDisable(GL_LIGHTING);

	int bufWidth, bufHeight;
	unsigned char *buffer;
	raytracer->getBuffer( buffer, bufWidth, bufHeight );

	static GLuint texName = 0;
	if( texName == 0 )
		glGenTextures(1, &texName);

	if( m_dirty && raytracer->isReady() )
	{
		m_dirty = false;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, texName);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
					   GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
					   GL_NEAREST);
		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, bufWidth, bufHeight, GL_RGB,
			GL_UNSIGNED_BYTE, buffer );
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_FLAT);

	glPushMatrix();
		const Camera& sceneCamera = raytracer->getScene().getCamera();
		glTranslated( (sceneCamera.getEye())[0],
					(sceneCamera.getEye())[1],
					(sceneCamera.getEye())[2] );
		
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		// Now need to draw the camera.
		glBegin( GL_LINES );
			glVertex3d(0,0,0);
			glVertex3dv( (sceneCamera.getLook() 
				+ 0.5*sceneCamera.getU() 
				+ 0.5*sceneCamera.getV()).getPointer() );
			glVertex3d(0,0,0);
			glVertex3dv( (sceneCamera.getLook() 
				+ 0.5*sceneCamera.getU() 
				- 0.5*sceneCamera.getV()).getPointer() );
			glVertex3d(0,0,0);
			glVertex3dv( (sceneCamera.getLook() 
				- 0.5*sceneCamera.getU() 
				+ 0.5*sceneCamera.getV()).getPointer() );
			glVertex3d(0,0,0);
			glVertex3dv( (sceneCamera.getLook() 
				- 0.5*sceneCamera.getU() 
				- 0.5*sceneCamera.getV()).getPointer() );
		glEnd();

		glTranslated( (sceneCamera.getLook())[0],
					(sceneCamera.getLook())[1],
					(sceneCamera.getLook())[2] );

		if( !m_dirty || raytracer->isReady() )
		{
			glColor4f( 1.0f, 1.0f, 1.0f, 0.7f );
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texName);
		}
		else
		{
			glColor4f( 0.0f, 0.0f, 0.0f, 0.7f );
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin( GL_QUADS );
			glTexCoord2f(0.0, 0.0);
			glVertex3dv((-0.5*sceneCamera.getU() - 0.5*sceneCamera.getV()).getPointer());

			glTexCoord2f(0.0, 1.0);
			glVertex3dv((-0.5*sceneCamera.getU() + 0.5*sceneCamera.getV()).getPointer());

			glTexCoord2f(1.0, 1.0);
			glVertex3dv((0.5*sceneCamera.getU() + 0.5*sceneCamera.getV()).getPointer());

			glTexCoord2f(1.0, 0.0);
			glVertex3dv((0.5*sceneCamera.getU() - 0.5*sceneCamera.getV()).getPointer());
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		glBegin( GL_LINE_STRIP );
			glVertex3dv((-0.51*sceneCamera.getU() - 0.51*sceneCamera.getV()).getPointer());
			glVertex3dv((-0.51*sceneCamera.getU() + 0.51*sceneCamera.getV()).getPointer());
			glVertex3dv((0.51*sceneCamera.getU() + 0.51*sceneCamera.getV()).getPointer());
			glVertex3dv((0.51*sceneCamera.getU() - 0.51*sceneCamera.getV()).getPointer());
			glVertex3dv((-0.51*sceneCamera.getU() - 0.51*sceneCamera.getV()).getPointer());
		glEnd();


	glPopMatrix();

	glEnable( GL_LIGHTING );
}
