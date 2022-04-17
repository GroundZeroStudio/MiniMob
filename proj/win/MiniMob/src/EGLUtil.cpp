#include "EGLUtil.h"

#ifdef _WIN64
#define GWL_USERDATA GWLP_USERDATA
#endif

EGLUtil::EGLUtil(void(*renderPipelineFunc)(), void(*updateFunc)())
{
	_renderPipelineFunc = renderPipelineFunc;
	_updateFunc = updateFunc;
}

LRESULT EGLUtil::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT  lRet = 1;

	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
	{
		EGLUtil *eglUtil = (EGLUtil *)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);
		eglUtil->_renderPipelineFunc();
		eglSwapBuffers(eglUtil->eglDisplay, eglUtil->eglSurface);
		ValidateRect(eglUtil->eglNativeWindow, NULL);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return lRet;
}

GLboolean EGLUtil::CreateWnd(const char *title, GLint width, GLint height)
{
	WNDCLASS wndclass = { 0 };
	DWORD    wStyle = 0;
	RECT     windowRect;
	HINSTANCE hInstance = GetModuleHandle(NULL);


	wndclass.style = CS_OWNDC;
	wndclass.lpfnWndProc = (WNDPROC)WindowProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = "opengles3.0";

	if (!RegisterClass(&wndclass))
	{
		return FALSE;
	}

	wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

	// Adjust the window rectangle so that the client area has
	// the correct number of pixels
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = width;
	windowRect.bottom = height;

	AdjustWindowRect(&windowRect, wStyle, FALSE);

	this->eglNativeWindow = CreateWindow(
		"opengles3.0",
		title,
		wStyle,
		0,
		0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

#ifdef _WIN64
   //In LLP64 LONG is stll 32bit.
	SetWindowLongPtr(this->eglNativeWindow, GWL_USERDATA, (LONGLONG)(LONG_PTR)this);
#else
	SetWindowLongPtr(this->eglNativeWindow, GWL_USERDATA, (LONG)(LONG_PTR)this);
#endif

	if (this->eglNativeWindow == NULL)
	{
		return GL_FALSE;
	}

	ShowWindow(this->eglNativeWindow, TRUE);

	return GL_TRUE;
}

EGLint GetContextRenderableType(EGLDisplay eglDisplay)
{
#ifdef EGL_KHR_create_context
	const char *extensions = eglQueryString(eglDisplay, EGL_EXTENSIONS);

	// check whether EGL_KHR_create_context is in the extension string
	if (extensions != NULL && strstr(extensions, "EGL_KHR_create_context"))
	{
		// extension is supported
		return EGL_OPENGL_ES3_BIT_KHR;
	}
#endif
	// extension is not supported
	return EGL_OPENGL_ES2_BIT;
}

GLboolean EGLUtil::CreateEGLWindow(const char *title, GLint width, GLint height)
{
	EGLConfig config;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };

	if (!this->CreateWnd(title, width, height))
	{
		return GL_FALSE;
	}

	this->eglDisplay = eglGetDisplay(this->eglNativeDisplay);
	if (this->eglDisplay == EGL_NO_DISPLAY)
	{
		return GL_FALSE;
	}

	// Initialize EGL
	if (!eglInitialize(this->eglDisplay, &majorVersion, &minorVersion))
	{
		return GL_FALSE;
	}

	{
		EGLint numConfigs = 0;
		EGLint attribList[] =
		{
		   EGL_RED_SIZE,       5,
		   EGL_GREEN_SIZE,     6,
		   EGL_BLUE_SIZE,      5,
		   EGL_ALPHA_SIZE,     EGL_DONT_CARE,
		   EGL_DEPTH_SIZE,     EGL_DONT_CARE,
		   EGL_STENCIL_SIZE,   EGL_DONT_CARE,
		   EGL_SAMPLE_BUFFERS, 0,
		   // if EGL_KHR_create_context extension is supported, then we will use
		   // EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
		   EGL_RENDERABLE_TYPE, GetContextRenderableType(this->eglDisplay),
		   EGL_NONE
		};

		// Choose config
		if (!eglChooseConfig(this->eglDisplay, attribList, &config, 1, &numConfigs))
		{
			return GL_FALSE;
		}

		if (numConfigs < 1)
		{
			return GL_FALSE;
		}
	}

	// Create a surface
	this->eglSurface = eglCreateWindowSurface(this->eglDisplay, config,
		this->eglNativeWindow, NULL);

	if (this->eglSurface == EGL_NO_SURFACE)
	{
		return GL_FALSE;
	}

	// Create a GL context
	this->eglContext = eglCreateContext(this->eglDisplay, config,
		EGL_NO_CONTEXT, contextAttribs);

	if (this->eglContext == EGL_NO_CONTEXT)
	{
		return GL_FALSE;
	}

	// Make the context current
	if (!eglMakeCurrent(this->eglDisplay, this->eglSurface,
		this->eglSurface, this->eglContext))
	{
		return GL_FALSE;
	}

	return GL_TRUE;
}

void EGLUtil::WindLoop()
{
	MSG msg = { 0 };
	int done = 0;

	while (!done)
	{
		int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);
		if (gotMsg)
		{
			if (msg.message == WM_QUIT)
				done = 1;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
			SendMessage(eglNativeWindow, WM_PAINT, 0, 0);
	}
}