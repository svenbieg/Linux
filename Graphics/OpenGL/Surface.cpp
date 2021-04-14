//=============
// Surface.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Surface.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace OpenGL {


//============================
// Con-/Destructors Protected
//============================

Surface::Surface(EGLDisplay display):
pDisplay(display),
pSurface(nullptr)
{}

Surface::~Surface()
{
if(pSurface)
	eglDestroySurface(pDisplay, pSurface);
}

}}