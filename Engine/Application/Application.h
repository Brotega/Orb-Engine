#pragma once
#include <vector>
#include <string>
#include "../AssetManager/AssetManager.h"

namespace OrbEngine
{
	constexpr int MAX_POINT_LIGHTS = 4;

	/* Forward Declarations */
	class Actor;
	class Camera;
	class DirectionalLight;
	class InputSystem;
	class Light;
	class PointLight;
	class RenderingSystem;
	class SpotLight;
	class UniformBuffer;
	class Window;


	class Application
	{
	public:
		/* Constructors/destructor */
		Application(int screenWidth, int screenHeight, float frameRate, const std::string& applicationName);
		~Application();

		/* Main functions */
		void AddActor(Actor* actor) { m_Actors.push_back(actor); }
		bool InitializeApplication();
		bool IsRunning() const { return m_IsRunning; }
		void RemoveActor(Actor* actor) { m_Actors.erase(std::find(m_Actors.begin(), m_Actors.end(), actor)); }
		void RunLoop();
		void Shutdown();

		/* Setters */
		void SetMainCamera(Camera* camera) { m_MainCamera = camera; }

		/* Getters */
		int GetScreenWidth() const { return m_ScreenWidth; }
		int GetScreenHeight() const { return m_ScreenHeight; }
		float GetTimeElapsed() const { return m_TimeElapsed; }
		float GetFramerate() const { return m_FrameRate; }
		std::string GetApplicationName() const { return m_ApplicationName; }
		Camera* GetMainCamera() const { return m_MainCamera; }
		RenderingSystem* GetRendereringSystem() const { return m_RenderingSystem; }
		AssetManager* GetAssetManager() const { return m_AssetManager; }
		InputSystem* GetInputSystem() const { return m_InputSystem; }
		std::vector<Actor*> GetActors() const { return m_Actors; }
		Window* GetWindow() const { return m_Window; }

	protected:
		AssetManager* m_AssetManager;
		Camera* m_MainCamera;
		InputSystem* m_InputSystem;
		RenderingSystem* m_RenderingSystem;
		Window* m_Window;

		/* Lights */
		DirectionalLight* m_DirectionalLight; // Max 1 for now
		SpotLight* m_SpotLight; // Max 1 for now
		PointLight* m_PointLights[MAX_POINT_LIGHTS]; // Max MAX_POINT_LIGHTS for now
		UniformBuffer* m_LightUniformBuffer;

		std::vector<Actor*> m_Actors;

		/* Application data */
		int m_ScreenWidth;
		int m_ScreenHeight;
		float m_FrameRate;
		float m_TimeElapsed;
		float m_TimeScale;
		const std::string m_ApplicationName;
		bool m_IsRunning;
		/*------------------*/

		/* Applications derived from this will implement their own */
		virtual bool Initialize() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void LateUpdate(float deltaTime) = 0;
		virtual void RenderFrame() = 0;
		virtual bool LoadScene() = 0;

	private:
		void InitializeLights();
		bool StoreDefaultShaders() const;
		bool StoreDefaultTextures() const;
		void StoreDefaultMaterials() const;
		void UpdateUniformBuffers() const;
	};
}