#pragma once

#include "Entite.h"

class GameApp2D : public Entite::Layer
{
public:

	GameApp2D();
	virtual ~GameApp2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Entite::Timestep ts) override;
	void OnEvent(Entite::Event& e) override;

	virtual void OnImGuiRender() override;
private:

	Entite::OrthographicCameraController m_CameraController;

	// Temp
	Entite::Ref<Entite::VertexArray> m_SquareVA;
	Entite::Ref<Entite::Shader> m_FlatColorShader;
	// Temp end
	Entite::Ref<Entite::Texture2D> m_CheckerboardTexture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};