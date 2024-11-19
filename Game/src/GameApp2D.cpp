#include "GameApp2D.h"

#include "imguiOrig/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GameApp2D::GameApp2D()
	: Layer("GameApp2D"), m_CameraController(1280.0f / 720.0f)
{
}

void GameApp2D::OnAttach()
{
}

void GameApp2D::OnDetach()
{
}

void GameApp2D::OnUpdate(Entite::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Entite::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Entite::RenderCommand::Clear();

	Entite::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Entite::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Entite::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Entite::Renderer2D::EndScene();
}

void GameApp2D::OnEvent(Entite::Event& e)
{
	m_CameraController.OnEvent(e);
}

void GameApp2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}