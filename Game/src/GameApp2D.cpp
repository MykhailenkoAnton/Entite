#include "GameApp2D.h"

#include "imguiOrig/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// temp timer start --
#include <chrono>

template <typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func) 
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		auto duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}

private:

	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResults) {m_ProfileResults.push_back(profileResults); })
// temp timer end --

GameApp2D::GameApp2D()
	: Layer("GameApp2D"), m_CameraController(1280.0f / 720.0f)
{
}

void GameApp2D::OnAttach()
{
	m_CheckerboardTexture = Entite::Texture2D::Create("assets/textures/Checkerboard.png");
}

void GameApp2D::OnDetach()
{
}

void GameApp2D::OnUpdate(Entite::Timestep ts)
{
	PROFILE_SCOPE("GameApp2D::OnUpdate");

	{
		// Update
		//Timer timer("CameraController::OnUpdate");
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		PROFILE_SCOPE("Renderer Prep");
		// Render
		Entite::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Entite::RenderCommand::Clear();
	}
	
	{
		PROFILE_SCOPE("Renderer Draw");
		Entite::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Entite::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Entite::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Entite::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		Entite::Renderer2D::EndScene();
	}
}

void GameApp2D::OnEvent(Entite::Event& e)
{
	m_CameraController.OnEvent(e);
}

void GameApp2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}