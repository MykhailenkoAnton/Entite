#include "Application.h"

#include "Entite/Events/ApplicationEvent.h"
#include "Entite/Log.h"

namespace Entite {

	Application::Application()
	{

	}

	Application::~Application()
	{


	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		HZ_TRACE(e);

		while (true)
		{

		}
	}
}