#pragma once

#ifdef ENT_PLATFORM_WINDOWS

extern Entite::Application* Entite::CreateApplication();

int main(int argc, char** argv)
{
	Entite::Log::Init();
	//ENT_CORE_WARN("Initializer log!");
	//ENT_INFO("123...!");

	ENT_PROFILE_BEGIN_SESSION("Startup", "EntiteProfile-Sratrup.json");
	auto app = Entite::CreateApplication();
	ENT_PROFILE_END_SESSION();

	ENT_PROFILE_BEGIN_SESSION("Runtime", "EntiteProfile-Runtime.json");
	app->Run();
	ENT_PROFILE_END_SESSION();

	ENT_PROFILE_BEGIN_SESSION("Shutdown", "EntiteProfile-Shutdown.json");
	delete app;
	ENT_PROFILE_END_SESSION();

	return 0;
}

#endif // ENT_PLATFORM_WINDOWS
