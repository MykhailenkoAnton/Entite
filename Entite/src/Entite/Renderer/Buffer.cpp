#include "entpch.h"
#include "Buffer.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Entite {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			ENT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;

		case RendererAPI::API::OpenGL: 
			return new OpenGLVertexBuffer(vertices, size);
		default:
			break;
		}


		ENT_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}


	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		default:
			break;
		}


		ENT_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}