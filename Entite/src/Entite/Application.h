#pragma once

#include "Core.h"

namespace Entite {

	class ENTITE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined on a CLIENT
	Application* CreateApplication();
}

