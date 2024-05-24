#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Entite/LayerStack.h"

#include "Entite/Events/ApplicationEvent.h"

#include "Entite/ImGui/ImGuiLayer.h"

#include "Entite/Renderer/Shader.h"

#include "Entite/Renderer/Buffer.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined on a CLIENT
	Application* CreateApplication();
}

