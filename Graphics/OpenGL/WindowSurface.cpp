//===================
// WindowSurface.cpp
//===================

#include "pch.h"


//=======
// Using
//=======

#include "WindowSurface.h"


//========
// Common
//========

namespace Graphics {
	namespace OpenGL {


//==================
// Con-/Destructors
//==================

WindowSurface::WindowSurface(EGLDisplay display, EGLConfig config, ANativeWindow* window):
Surface(display)
{
pSurface=eglCreateWindowSurface(display, config, window, nullptr);
}

}}