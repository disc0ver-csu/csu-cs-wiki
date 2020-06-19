// DebuggingView.h

// This is the base class for all your models.  It contains
// a camera control for your use.  The draw() function will 
// set up default lighting and apply the projection, so if you 
// inherit, you will probably want to call DebuggingView::draw()
// to set up the camera.

#ifndef DebuggingView_H
#define DebuggingView_H

#include "Fl_Gl_Window.H"

class ModelerCamera;
class RayTracer;

class DebuggingView : public Fl_Gl_Window
{
public:
	enum ShadingMode 
	{ NORMAL, WIREFRAME, FLAT_SHADING, };

	enum Quality
	{ HIGH_QUALITY, MEDIUM_QUALITY, LOW_QUALITY, POOR_QUALITY, };

	enum LightingMode
	{ SCENE_LIGHTING, DEFAULT_LIGHTING, };

    
	DebuggingView(int x, int y, int w, int h, char *label=0);

	virtual ~DebuggingView();
    virtual int handle(int event);
    virtual void draw();

	void drawAxes();
	void drawLights();
	void lightScene();
	void drawScene();
	void drawRays();
	void drawCamera();


    ModelerCamera *m_camera;

	void setRayTracer(RayTracer *tracer);

	void setShadingMode( ShadingMode mode )		{ m_shadingMode = mode; }
	void setQuality( Quality quality )			{ m_quality = quality; }
	void setLighting( LightingMode mode )		{ m_lightingMode = mode; }
	void setUseSceneMaterials( bool value )		{ m_useSceneMaterials = value; }
	void setUseSceneTextures( bool value )		{ m_useSceneTextures = value; }

	void setShowGeometry( bool value )			{ m_showGeometry = value; }
	void setShowLights( bool value )			{ m_showLights = value; }
	void setShowCamera( bool value )			{ m_showCamera = value; }
	void setShowAxes( bool value )				{ m_showAxes = value; }
	void setShowNormals( bool value )			{ m_showNormals = value; }

	void setShowVisibilityRays( bool value )	{ m_showVisibilityRays = value; }
	void setShowReflectionRays( bool value )	{ m_showReflectionRays = value; }
	void setShowRefractionRays( bool value )	{ m_showRefractionRays = value; }
	void setShowShadowRays( bool value )		{ m_showShadowRays = value; }

	void setDirty()								{ m_dirty = true; }

	void resetCamera();
private:
	RayTracer*			raytracer;

	ShadingMode			m_shadingMode;
	Quality				m_quality;
	LightingMode		m_lightingMode;
	bool				m_useSceneMaterials;
	bool				m_useSceneTextures;

	bool				m_dirty;

	bool				m_showGeometry;
	bool				m_showLights;
	bool				m_showCamera;
	bool				m_showAxes;
	bool				m_showNormals;

	bool				m_showVisibilityRays;
	bool				m_showReflectionRays;
	bool				m_showRefractionRays;
	bool				m_showShadowRays;
};


#endif
