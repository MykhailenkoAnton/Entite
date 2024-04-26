#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Entite/LayerStack.h"

#include "Entite/Events/ApplicationEvent.h"

namespace Entite {

	class ENTITE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	// To be defined on a CLIENT
	Application* CreateApplication();
}

