#pragma once

#include "OrthographicCamera.h"

namespace Entite {

	class Renderer2D
	{
	public:

		static void Init();
		static void Shutdowm();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitivies
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

	private:
	};
}