#include "Window.h"

#include "../Application/Application.h"

#include <glad/glad.h>

namespace OrbEngine
{
	Window::Window() : 
		m_WindowHandle(nullptr), m_GLContext(nullptr)
	{

	}

	Window::~Window()
	{

	}

	bool Window::Initialize(Application* application)
	{
		m_Width = application->GetScreenWidth();
		m_Height = application->GetScreenHeight();

		m_WindowHandle = SDL_CreateWindow(application->GetApplicationName().c_str(), 100, 100, m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!m_WindowHandle)
		{
			SDL_Log("Failed to create window: %s", SDL_GetError());
			return false;
		}

		/* Set OpenGL 4.2 attributes */
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		m_GLContext = SDL_GL_CreateContext(m_WindowHandle);

		/* Load OpenGL */
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			SDL_Log("Unable to load OpenGL");
			return false;
		}

		return true;
	}

	void Window::Present() const
	{
		SDL_GL_SwapWindow(m_WindowHandle);
	}

	void Window::Shutdown()
	{
		SDL_GL_DeleteContext(m_GLContext);
		SDL_DestroyWindow(m_WindowHandle);
	}
}