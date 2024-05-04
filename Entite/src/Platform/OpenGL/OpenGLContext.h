#pragma once

#include "Entite/Renderer/GraphicsContexti.h"

struct GLFWwindow;

namespace Entite {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:

		GLFWwindow* m_windowHandle;
	};
}