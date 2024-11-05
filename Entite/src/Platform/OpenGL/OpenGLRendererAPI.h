#pragma once

#include "Entite/Renderer/RendererAPI.h"

namespace Entite {

	class OpenGLRendereAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};
}