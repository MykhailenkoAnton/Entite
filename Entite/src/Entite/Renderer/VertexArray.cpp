#include "entpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Entite {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		default:
			break;
		}


		ENT_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}