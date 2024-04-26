#include "Entite.h"


class ExampleLayer : public Entite::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		ENT_INFO("ExampleLayer OnUpdate");
	}

	void OnEvent(Entite::Event& event) override
	{
		ENT_INFO("{0}", event);
	}

};


class Game : public Entite::Application
{
public:
	Game()
	{
		PushLayer(new ExampleLayer());
	}
	~Game()
	{

	}
};

Entite::Application* Entite::CreateApplication()
{
	
	return new Game();
}