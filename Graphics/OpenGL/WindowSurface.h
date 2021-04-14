//=================
// WindowSurface.h
//=================

#pragma once


//=======
// Using
//=======

#include "Surface.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace OpenGL {


//================
// Window-Surface
//================

class WindowSurface: public Surface
{
public:
	// Con-/Destructors
	WindowSurface(EGLDisplay Display, EGLConfig Configuration, ANativeWindow* Window);
};

}}