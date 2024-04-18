#pragma once

#ifdef ENT_PLATFORM_WINDOWS

extern Entite::Application* Entite::CreateApplication();

int main(int argc, char** argv)
{
	//Entite::Log::Init();

	auto app = Entite::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif // ENT_PLATFORM_WINDOWS
