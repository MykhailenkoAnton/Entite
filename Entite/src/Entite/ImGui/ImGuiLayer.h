#pragma once

#include "Entite/Layer.h"

#include "Entite/Events/KeyEvent.h"
#include "Entite/Events/MouseEvent.h"
#include "Entite/Events/ApplicationEvent.h"

namespace Entite {

	class ENTITE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseButtonMovedEvent(MouseMovedEvent& e);
		bool OnMouseButtonScrollEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowsResizeEvent(WindowResizeEvent& e);

	private:

		float m_Time = 0.0f;

	};
}