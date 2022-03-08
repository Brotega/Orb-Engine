#pragma once

#include <SDL2/SDL.h>

namespace OrbEngine
{
	/* Forward declarations */
	class Application;

	class Window
	{
	public:
		/* Constructors/destructor */
		Window();
		~Window();

		/* Main functions */
		bool Initialize(Application* application);
		void Present() const;
		void Shutdown();

		/* Setters */
		void SetWidth(int width) { m_Width = width; }
		void SetHeight(int height) { m_Height = height; }
		void SetWidthAndHeight(int width, int height) { m_Width = width; m_Height = height; }

		/* Getters */
		SDL_Window* GetWindowHandle() const { return m_WindowHandle; }
		SDL_GLContext GetGLContext() const { return m_GLContext; }

	private:
		SDL_Window* m_WindowHandle;
		SDL_GLContext m_GLContext;
		int m_Width;
		int m_Height;
	};
}