#include "entpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Entite {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Entite::ShaderDataType::None:

		case Entite::ShaderDataType::Float:
			return GL_FLOAT;
		case Entite::ShaderDataType::Float2:
			return GL_FLOAT;
		case Entite::ShaderDataType::Float3:
			return GL_FLOAT;
		case Entite::ShaderDataType::Float4:
			return GL_FLOAT;
		case Entite::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Entite::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Entite::ShaderDataType::Int:
			return GL_INT;
		case Entite::ShaderDataType::Int2:
			return GL_INT;
		case Entite::ShaderDataType::Int3:
			return GL_INT;
		case Entite::ShaderDataType::Int4:
			return GL_INT;
		case Entite::ShaderDataType::Bool:
			return GL_BOOL;
		}

		ENT_CORE_ASSERT(false, "Unknown Shader Data Type");
		return 0;
	};

	OpenGLVertexArray::OpenGLVertexArray()
	{
		ENT_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		ENT_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		ENT_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		ENT_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ENT_PROFILE_FUNCTION();

		ENT_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		ENT_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}