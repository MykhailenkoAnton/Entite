#include "entpch.h"
#include "Application.h"

#include "Entite/Events/ApplicationEvent.h"


#include <GLFW/glfw3.h>

namespace Entite {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{


	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}