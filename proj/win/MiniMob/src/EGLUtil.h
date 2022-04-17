#ifndef __EGL_UTIL_H__
#define __EGL_UTIL_H__
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <windows.h>

class EGLUtil
{
public:
	EGLUtil(void(*_renderPipelineFunc)(), void(*_updateFunc)());

	GLboolean CreateEGLWindow(const char *title, GLint width, GLint height);

	void WindLoop();
private:
	GLboolean CreateWnd(const char *title, GLint width, GLint height);

	static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// Display handle
	EGLNativeDisplayType eglNativeDisplay;

	/// Window handle
	EGLNativeWindowType  eglNativeWindow;

	/// EGL display
	EGLDisplay  eglDisplay;

	/// EGL context
	EGLContext  eglContext;

	/// EGL surface
	EGLSurface  eglSurface;

private:
	void(*_renderPipelineFunc)();
	void(*_updateFunc)();
};
#endif