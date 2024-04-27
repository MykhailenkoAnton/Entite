#pragma once

#include "Entite/Layer.h"

namespace Entite {

	class ENTITE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	private:

		float m_Time = 0.0f;
	};
}