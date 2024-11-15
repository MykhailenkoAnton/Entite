#include "entpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Entite {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle)
	{
		ENT_CORE_ASSERT(windowHandle, "windowHandle is NULL!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENT_CORE_ASSERT(status, "Failed to initialize Glad!");

		ENT_CORE_INFO("OpenGL Info:");
		ENT_CORE_INFO("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		ENT_CORE_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		ENT_CORE_INFO("Version: {0}", (const char*)glGetString(GL_VERSION));

		ENT_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}