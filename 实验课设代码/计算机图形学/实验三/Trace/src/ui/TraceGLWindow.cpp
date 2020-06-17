// TraceGLWindow
// A subclass of FL_GL_Window that handles drawing the traced image to the screen
// 
#include <iostream>

#include "TraceGLWindow.h"
#include "../RayTracer.h"
#include "GraphicalUI.h"

#include "../fileio/imageio.h"

extern bool debugMode;
extern TraceUI* traceUI;

TraceGLWindow::TraceGLWindow(int x, int y, int w, int h, const char *l)
			: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth = w;
	m_nWindowHeight = h;
	// Do not allow the user to re-size the window
	size_range(w, h, w, h);
}

int TraceGLWindow::handle(int event)
{
	// disable all mouse and keyboard events
	if(event == FL_PUSH ||
		event == FL_DRAG)
	{
		int x = Fl::event_x();
		int y = Fl::event_y();
		if(x < 0) x = 0;
		if(x > m_nWindowWidth) x = m_nWindowWidth;
		if(y < 0) y = 0;
		if(y > m_nWindowHeight) y = m_nWindowHeight;

		// Flip for FL's upside-down window coords
		y = m_nWindowHeight - y;

		if(raytracer) 
		{
			std::cout << "Tracing ray at " << x << ", " << y << std::endl;
			// Have we re-sized since drawing?
			if(!raytracer->isReady()) 
				raytracer->traceSetup(m_nWindowWidth, m_nWindowHeight);

			debugMode = true;
			raytracer->tracePixel( x, y );

			((GraphicalUI*) traceUI)->m_debuggingWindow->m_debuggingView->redraw();
			debugMode = false;
			refresh();

			
			if (Fl::damage()) {
				Fl::flush();
			}
		}
	}
	return 1;
}

void TraceGLWindow::draw()
{
	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		m_nWindowWidth=w();
		m_nWindowHeight=h();
	}

	glClear( GL_COLOR_BUFFER_BIT );

	unsigned char* buf;
	raytracer->getBuffer(buf, m_nDrawWidth, m_nDrawHeight);

	if ( buf ) {
		// just copy image to GLwindow conceptually
		glRasterPos2i( 0, 0 );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ROW_LENGTH, m_nDrawWidth );
		glDrawBuffer( GL_BACK );
		glDrawPixels( m_nDrawWidth, m_nDrawHeight, GL_RGB, GL_UNSIGNED_BYTE, buf );
	}
		
	glFlush();
}

void TraceGLWindow::refresh()
{
	redraw();
}

void TraceGLWindow::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
	// Do not allow manual re-sizing
	size_range(w(), h(), w(), h());
	m_nWindowWidth=w();
	m_nWindowHeight=h();
}

void TraceGLWindow::saveImage(const char *iname, const char *type, int quality)
{
	unsigned char* buf;

	raytracer->getBuffer(buf, m_nDrawWidth, m_nDrawHeight);
	if (buf)
		save(iname, buf, m_nDrawWidth, m_nDrawHeight, type, quality);
}

void TraceGLWindow::setRayTracer(RayTracer *tracer)
{
	raytracer = tracer;
}

