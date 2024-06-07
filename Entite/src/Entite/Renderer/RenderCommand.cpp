#include "entpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Entite {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendereAPI;
}