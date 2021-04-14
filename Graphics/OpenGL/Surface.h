//===========
// Surface.h
//===========

#pragma once


//=======
// Using
//=======

#include <EGL/egl.h>


//===========
// Namespace
//===========

namespace Graphics {
	namespace OpenGL {


//=========
// Surface
//=========

class Surface: public Object
{
public:
	// Common
	EGLSurface GetSurface()const { return pSurface; }

protected:
	// Con-/Destructors
	Surface(EGLDisplay Display);
	~Surface();

	// Common
	EGLDisplay pDisplay;
	EGLSurface pSurface;
};

}}