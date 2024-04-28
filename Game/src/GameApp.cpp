#include "Entite.h"


class ExampleLayer : public Entite::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		//ENT_WARN("ExampleLayer OnUpdate");

		if (Entite::Input::IsKeyPressed(ENT_KEY_TAB))
		{
			ENT_INFO("Preesed poll");
		}
	}

	void OnEvent(Entite::Event& event) override
	{
		//ENT_INFO("{0}", event);
		if (event.GetEventType() == Entite::EventType::KeyPressed)
		{
			Entite::KeyPressedEvent& e = (Entite::KeyPressedEvent&)event;
			if (e.GetKeyCode() == ENT_KEY_TAB)
			{
				ENT_INFO("ENT_KEY_TAB Preesed");
			}
			ENT_INFO("{0}", (char)e.GetKeyCode());
		}
	}

};


class Game : public Entite::Application
{
public:
	Game()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Entite::ImGuiLayer());
	}
	~Game()
	{

	}
};

Entite::Application* Entite::CreateApplication()
{
	
	return new Game();
}