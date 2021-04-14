//===================
// DeviceContext.cpp
//===================

#include "pch.h"


//=======
// Using
//=======

#include <GLES/gl.h>
#include "DeviceContext.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace OpenGL {


//==================
// Con-/Destructors
//==================

DeviceContext::DeviceContext():
iFormat(-1),
pConfiguration(nullptr),
pDisplay(EGL_NO_DISPLAY)
{
pDisplay=eglGetDisplay(EGL_DEFAULT_DISPLAY);
eglInitialize(pDisplay, 0, 0);
EGLint attribs[]=
	{
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	EGL_BLUE_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_RED_SIZE, 8,
	EGL_NONE
	};
EGLint config_count;
eglChooseConfig(pDisplay, attribs, &pConfiguration, 1, &config_count);
EGLint format;
eglGetConfigAttrib(pDisplay, pConfiguration, EGL_NATIVE_VISUAL_ID, &iFormat);
pContext=eglCreateContext(pDisplay, pConfiguration, NULL, NULL);
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
glEnable(GL_CULL_FACE);
glShadeModel(GL_SMOOTH);
glDisable(GL_DEPTH_TEST);
}

DeviceContext::~DeviceContext()
{
eglMakeCurrent(pDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_DISPLAY);
hTarget=nullptr;
eglDestroyContext(pDisplay, pContext);
eglTerminate(pDisplay);
}


//========
// Common
//========

VOID DeviceContext::Clear(COLOR c)
{
GLfloat r=(GLfloat)c.GetRed()/255;
GLfloat g=(GLfloat)c.GetGreen()/255;
GLfloat b=(GLfloat)c.GetBlue()/255;
GLfloat a=(GLfloat)c.GetAlpha()/255;
glClearColor(r, g, b, a);
glClear(GL_COLOR_BUFFER_BIT);
}

VOID DeviceContext::DrawText(Handle<String> text, COLOR c)
{
}

VOID DeviceContext::FillRect(RECT const& rc, COLOR c)
{
}

VOID DeviceContext::Flush()
{
if(!hTarget)
	return;
auto surface=hTarget->GetSurface();
eglSwapBuffers(pDisplay, surface);
}

SIZE DeviceContext::MeasureText(Handle<Graphics::Font> Font, Handle<String> Text)
{
return SIZE(0, 0);
}

VOID DeviceContext::SetPixel(INT x, INT y, COLOR c)
{
}

VOID DeviceContext::SetTarget(Handle<Surface> target)
{
hTarget=target;
auto surface=hTarget? hTarget->GetSurface(): EGL_NO_SURFACE;
eglMakeCurrent(pDisplay, surface, surface, pContext);
EGLint width=0;
EGLint height=0;
if(surface)
	{
	eglQuerySurface(pDisplay, surface, EGL_WIDTH, &width);
	eglQuerySurface(pDisplay, surface, EGL_HEIGHT, &height);
	}
Clip.Left=0;
Clip.Top=0;
Clip.Right=width;
Clip.Bottom=height;
Offset.Left=0;
Offset.Top=0;
}

}}