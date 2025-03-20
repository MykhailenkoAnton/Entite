#include "Entite.h"
#include "Entite/Core/EntryPoint.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGuiDocking/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameApp2D.h"

class ExampleLayer : public Entite::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = Entite::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.9f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		Entite::Ref<Entite::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Entite::VertexBuffer::Create(vertices, sizeof(vertices)));
		Entite::BufferLayout layout = {
				{Entite::ShaderDataType::Float3, "a_Position" },
				{Entite::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Entite::Ref<Entite::IndexBuffer> indexBuffer;
		indexBuffer.reset(Entite::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Entite::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		};
		Entite::Ref<Entite::VertexBuffer> squareBP; 
		squareBP.reset(Entite::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareBP->SetLayout({
			{Entite::ShaderDataType::Float3, "a_Position" },
			{Entite::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareBP);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Entite::Ref<Entite::IndexBuffer> squareIB; 
		squareIB.reset((Entite::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
			
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
			
		)";

		m_Shader = Entite::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
			
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
			
		)";

		m_FlatColorShader = Entite::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
	
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Entite::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Entite::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Entite::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Entite::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Entite::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Entite::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Entite::RenderCommand::Clear();

		Entite::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Entite::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Entite::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int x = 0; x < 20; x++)
		{
			for (int i = 0; i < 20; i++)
			{
				glm::vec3 pos(i * 0.11f, x * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Entite::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Entite::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Entite::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//triangle
		//Entite::Renderer::Submit(m_Shader, m_VertexArray);

		Entite::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Entite::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	
	Entite::ShaderLibrary m_ShaderLibrary;

	Entite::Ref<Entite::Shader> m_Shader;
	Entite::Ref<Entite::VertexArray> m_VertexArray;

	Entite::Ref<Entite::Shader> m_FlatColorShader;
	Entite::Ref<Entite::VertexArray> m_SquareVA;

	Entite::Ref<Entite::Texture2D> m_Texture, m_ChernoLogoTexture;

	Entite::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};


class Game : public Entite::Application
{
public:
	Game()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new GameApp2D());
	}
	~Game()
	{

	}
};

Entite::Application* Entite::CreateApplication()
{
	return new Game();
}