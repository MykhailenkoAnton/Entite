#include "Entite.h"

class Game : public Entite::Application
{
public:
	Game()
	{

	}
	~Game()
	{

	}
};

Entite::Application* Entite::CreateApplication()
{
	return new Game();
}