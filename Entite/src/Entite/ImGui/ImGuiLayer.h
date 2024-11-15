#pragma once

#include "Entite/Core/Layer.h"

#include "Entite/Events/KeyEvent.h"
#include "Entite/Events/MouseEvent.h"
#include "Entite/Events/ApplicationEvent.h"

namespace Entite {

	class ENTITE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		//void OnEvent(Event& event);
		void Begin();
		void End();

		/*bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseButtonMovedEvent(MouseMovedEvent& e);
		bool OnMouseButtonScrollEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowsResizeEvent(WindowResizeEvent& e);*/

	private:

		float m_Time = 0.0f;

	};
}