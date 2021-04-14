//=================
// DeviceContext.h
//=================

#pragma once


//=======
// Using
//=======

#include "Graphics/DeviceContext.h"
#include "Surface.h"


//===========
// Namespace
//===========

namespace Graphics {
	namespace OpenGL {


//================
// Device-Context
//================

class DeviceContext: public Graphics::DeviceContext
{
public:
	// Con-/Destructors
	DeviceContext();
	~DeviceContext();

	// Common
	VOID Clear(COLOR Color=0)override;
	VOID DrawText(Handle<String> Text, COLOR Color=0)override;
	VOID FillRect(RECT const& Rect, COLOR Color)override;
	VOID Flush()override;
	EGLConfig GetConfiguration()const { return pConfiguration; }
	EGLContext GetContext()const { return pContext; }
	EGLDisplay GetDisplay()const { return pDisplay; }
	EGLint GetFormat()const { return iFormat; }
	SIZE MeasureText(Handle<Graphics::Font> Font, Handle<String> Text)override;
	VOID SetPixel(INT Left, INT Top, COLOR Color)override;
	VOID SetTarget(Handle<Surface> Target);

private:
	// Common
	EGLint iFormat;
	Handle<Surface> hTarget;
	EGLConfig pConfiguration;
	EGLContext pContext;
	EGLDisplay pDisplay;
};

}}