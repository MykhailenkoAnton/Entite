#include "GameApp2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imguiOrig/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GameApp2D::GameApp2D()
	: Layer("GameApp2D"), m_CameraController(1280.0f / 720.0f)
{
}

void GameApp2D::OnAttach()
{
	m_SquareVA = Entite::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	Entite::Ref<Entite::VertexBuffer> squareBP;
	squareBP.reset(Entite::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareBP->SetLayout({
		{Entite::ShaderDataType::Float3, "a_Position" },
		});
	m_SquareVA->AddVertexBuffer(squareBP);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Entite::Ref<Entite::IndexBuffer> squareIB;
	squareIB.reset((Entite::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Entite::Shader::Create("assets/shaders/FlatColor.glsl");
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

	Entite::Renderer::BeginScene(m_CameraController.GetCamera());


	std::dynamic_pointer_cast<Entite::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Entite::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Entite::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Entite::Renderer::EndScene();
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