/*----------------------------------------------
Adapted from http://www.swiftless.com/tutorials/opengl4/1-opengl-window.html
into a class Date: 2015/06
----------------------------------------------*/

#ifndef __GLSystemSingleton_H_
#define __GLSystemSingleton_H_

#include "RE\system\WindowClass.h"

#include <GL\glew.h>
#include <GL\wglew.h>

namespace ReEng
{

class ReEngDLL GLSystemSingleton
{
	//--Members
	HDC   m_hDC = NULL;		// Private GDI Device Context
	HGLRC m_hRC = NULL;		// Permanent Rendering Context
	float m_fGLVersion = 0.0f; // OpenGL version
	bool m_bForceOldGL = false;	// Forces OpenGL 2.1 to be initialized
public:
	//--Methods

	/*
	HRESULT InitGLDevice(HWND g_hWnd);
		Initializes the OpenGL Device Context
	Arguments:
		HWND g_hWnd -> Window Handler
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	HRESULT InitGLDevice(HWND g_hWnd);

	/*
	int DrawOldGLScene(GLvoid);
		Draws a demo scene using OpenGL 2.1 Context, used only if
		failed to initialize 3.x+ in the system
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int DrawOldGLScene(GLvoid);
	
	/*
	static GLSystemSingleton* GetInstance(void);
		Singleton Accessor, returns the singleton of this class
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	static GLSystemSingleton* GetInstance(void);

	
	/*
	void ReleaseInstance(void);
		Releases the singleton of this class
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);
	
	/*
	HDC GetDeviceContext(GLvoid);
		Returns the OpenGL rendering context device
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	HDC GetDeviceContext(GLvoid);

	/*
	float GetGLVersion(void);
		Returns the OpenGL Version the program is running
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	float GetGLVersion(void);

	/*
	bool IsNewOpenGLRunning(void);
		Returns whether OpenGL3.x or newer is running
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	bool IsNewOpenGLRunning(void);

	/*
	void ForceOldOpenGL(bool input = true);
		Forces OpenGL 2.1 to be used for the rendering context
	*/
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void ForceOldOpenGL(bool a_bInput = true);

	/*
	void GLSwapBuffers(void);
		SwapsvOpenGL buffer
	*/
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void GLSwapBuffers(void);

private:
	//--Methods
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	GLSystemSingleton(void); // Constructor
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	GLSystemSingleton(GLSystemSingleton const& other); //Copy Constructor
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	GLSystemSingleton& operator=(GLSystemSingleton const& other); // Copy Assignment Operator
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	~GLSystemSingleton(void); // Destructor

	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void); // Release Memory
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void); // Initialize variables
	
	static GLSystemSingleton* m_pInstance; // Singleton
};

}

#include "ShaderCompiler.h"

#endif /*__GLSystemSingleton_H__*/