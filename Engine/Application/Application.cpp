#include "Application.h"
#include "../Actors/Actor.h"
#include "../Actors/Testing/FreeMoveCamera.h"
#include "../Components/Component.h"
#include "../Components/Light.h"
#include "../Components/Camera.h"
#include "../Components/Transform.h"
#include "../Input/InputSystem.h"
#include "../Debugging/CoordinateSystem.h"
#include "../Debugging/Grid.h"
#include "../Rendering/Material.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/RenderingSystem.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Texture2D.h"
#include "../Rendering/Buffer/UniformBuffer.h"
#include "../Window/Window.h"

#define STB_IMAGE_IMPLEMENTATION
#include <Third Party/stb_image.h>

namespace OrbEngine
{
	Application::Application(int screenWidth, int screenHeight, float frameRate, const std::string& applicationName) :
		m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight),
		m_FrameRate(frameRate), m_ApplicationName(applicationName),
		m_IsRunning(true), m_TimeElapsed(0.0f),
		m_MainCamera(nullptr), m_RenderingSystem(nullptr),
		m_AssetManager(nullptr),
		m_DirectionalLight(nullptr), m_SpotLight(nullptr),
		m_PointLights{ nullptr }, m_TimeScale(1.0f)
	{

	}

	Application::~Application()
	{
		// Note: It's better to de-allocate in Shutdown() than here in case Initialize() returns false
		// and nothing gets allocated in the first place
	}

	bool Application::InitializeApplication()
	{
		// Initiailize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		{
			SDL_Log("Unable to initialize SDL2: %s", SDL_GetError());
			return false;
		}

		// Initialize window
		m_Window = new Window();
		if (!m_Window->Initialize(this))
		{
			delete m_Window;
			return false;
		}

		// Create asset manager
		m_AssetManager = new AssetManager();

		if (!StoreDefaultShaders()) return false;
		if (!StoreDefaultTextures()) return false;
		StoreDefaultMaterials();

		m_InputSystem = new InputSystem(this);
		m_RenderingSystem = new RenderingSystem(this);

		InitializeLights();

		/* For image loading */
		stbi_set_flip_vertically_on_load(true);

		m_MainCamera = new Camera();
		m_MainCamera->SetAllCameraParameters(0.01f, 1000.0f, static_cast<float>(m_ScreenWidth), static_cast<float>(m_ScreenHeight), 60.0f);

		Initialize();
		LoadScene();

		m_TimeElapsed = static_cast<float>(SDL_GetTicks());

		return true;
	}

	void Application::RunLoop()
	{
		/* Check for when user closes out of application using the X button */
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				m_IsRunning = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					m_ScreenWidth = event.window.data1;
					m_ScreenHeight = event.window.data2;
					m_RenderingSystem->SetViewport(m_ScreenWidth, m_ScreenHeight);
					m_MainCamera->SetWidth(static_cast<float>(m_ScreenWidth));
					m_MainCamera->SetHeight(static_cast<float>(m_ScreenHeight));
				}
				break;
			}
		}

		m_InputSystem->ProcessInput(); // This should come first in the process input part of the loop
		
		// Set up ESC and F1 (debug) commands
		if (m_InputSystem->GetKeyDown(InputSystem::KEYBOARD_ESCAPE)) m_IsRunning = false;

		ProcessInput();

		/* Cap to m_FrameRate value - default set to 60fps in Application constructor */
		float currTick = static_cast<float>(SDL_GetTicks());
		while ((currTick - m_TimeElapsed) < (1000.0f / m_FrameRate))
		{
			currTick = static_cast<float>(SDL_GetTicks());
		}
		float deltaTime = (currTick - m_TimeElapsed) / 1000.0f;
		m_TimeElapsed = static_cast<float>(SDL_GetTicks());
		deltaTime *= m_TimeScale;

		Update(deltaTime);
		LateUpdate(deltaTime);
		UpdateUniformBuffers();
		RenderFrame();
		m_Window->Present();
	}

	void Application::Shutdown()
	{
		delete m_LightUniformBuffer;
		
		for (int i = 0; i < MAX_POINT_LIGHTS; ++i)
		{
			delete m_PointLights[i];
		}
		delete m_SpotLight;
		delete m_DirectionalLight;

		delete m_InputSystem;

		delete m_MainCamera;

		for (size_t i = 0; i < m_Actors.size(); i++)
		{
			delete m_Actors[i];
		}

		m_Actors.clear();

		delete m_RenderingSystem;

		delete m_AssetManager;

		SDL_Quit();

		delete m_Window;
	}

	void Application::InitializeLights()
	{
		m_DirectionalLight = new DirectionalLight();
		m_DirectionalLight->SetEnabled(true);
		m_DirectionalLight->SetAmbientColor(Color(0.3f, 0.3f, 0.3f));
		m_DirectionalLight->SetDiffuseColor(Color(0.3f, 0.3f, 0.3f));
		m_DirectionalLight->SetSpecularColor(Color(0.2f, 0.2f, 0.2f));
		m_SpotLight = new SpotLight();
		m_SpotLight->SetEnabled(false);
		for (int i = 0; i < MAX_POINT_LIGHTS; ++i)
		{
			m_PointLights[i] = new PointLight();
			m_PointLights[i]->SetEnabled(false);
		}

		Actor* dirLightActor = new Actor(this);
		Actor* spotLightActor = new Actor(this);
		spotLightActor->SetEnabled(false);
		Actor* pointLightActor0 = new Actor(this);
		pointLightActor0->SetEnabled(false);
		Actor* pointLightActor1 = new Actor(this);
		pointLightActor1->SetEnabled(false);
		Actor* pointLightActor2 = new Actor(this);
		pointLightActor2->SetEnabled(false);
		Actor* pointLightActor3 = new Actor(this);
		pointLightActor3->SetEnabled(false);


		dirLightActor->AddComponent(m_DirectionalLight);
		spotLightActor->AddComponent(m_SpotLight);
		pointLightActor0->AddComponent(m_PointLights[0]);
		pointLightActor1->AddComponent(m_PointLights[1]);
		pointLightActor2->AddComponent(m_PointLights[2]);
		pointLightActor3->AddComponent(m_PointLights[3]);

		m_LightUniformBuffer = new UniformBuffer(1, sizeof(LightingUniform));
	}

	bool Application::StoreDefaultShaders() const
	{
		Shader* defaultLitShader = new Shader();
		if (defaultLitShader->Load("DefaultLit_Vert.glsl", "DefaultLit_Frag.glsl"))
		{
			m_AssetManager->StoreShader("Lit", defaultLitShader);
		}
		else
		{
			delete defaultLitShader;
			return false;
		}

		Shader* defaultUnlitShader = new Shader();
		if (defaultUnlitShader->Load("DefaultUnlit_Vert.glsl", "DefaultUnlit_Frag.glsl"))
		{
			m_AssetManager->StoreShader("Unlit", defaultUnlitShader);
		}
		else
		{
			delete defaultUnlitShader;
			return false;
		}

		Shader* debugShader = new Shader();
		if (debugShader->Load("Debug_Vert.glsl", "Debug_Frag.glsl"))
		{
			m_AssetManager->StoreShader("Debug", debugShader);
		}
		else
		{
			delete debugShader;
			return false;
		}

		Shader* uiShader = new Shader();
		if (uiShader->Load("UI_Vert.glsl", "UI_Frag.glsl"))
		{
			m_AssetManager->StoreShader("UI", uiShader);
		}
		else
		{
			delete uiShader;
			return false;
		}

		Shader* skyboxShader = new Shader();
		if (skyboxShader->Load("Skybox_Vert.glsl", "Skybox_Frag.glsl"))
		{
			m_AssetManager->StoreShader("Skybox", skyboxShader);
		}
		else
		{
			delete skyboxShader;
			return false;
		}

		return true;
	}

	bool Application::StoreDefaultTextures() const
	{
		Texture2D* whiteTexture = new Texture2D();
		if (whiteTexture->Load("Default/White.png", TextureType::DEFAULT))
		{
			m_AssetManager->StoreTexture("White", whiteTexture);
		}
		else
		{
			delete whiteTexture;
			return false;
		}

		Texture2D* blackTexture = new Texture2D();
		if (blackTexture->Load("Default/Black.png", TextureType::DEFAULT))
		{
			m_AssetManager->StoreTexture("Black", blackTexture);
		}
		else
		{
			delete blackTexture;
			return false;
		}

		Texture2D* grayTexture = new Texture2D();
		if (grayTexture->Load("Default/Gray.png", TextureType::DEFAULT))
		{
			m_AssetManager->StoreTexture("Gray", grayTexture);
		}
		else
		{
			delete grayTexture;
			return false;
		}

		return true;
	}

	void Application::StoreDefaultMaterials() const
	{
		Material* litMaterial = new Material();
		litMaterial->SetShader(m_AssetManager->GetShader("Lit"));
		m_AssetManager->StoreMaterial("MAT_Lit", litMaterial);

		Material* unlitMaterial = new Material();
		unlitMaterial->SetShader(m_AssetManager->GetShader("Unlit"));
		m_AssetManager->StoreMaterial("MAT_Unlit", unlitMaterial);

		Material* skyboxMaterial = new Material();

		return;
	}

	void Application::UpdateUniformBuffers() const
	{

		Vector3 DL_Direction = m_DirectionalLight->GetActor()->GetTransform()->GetForward();
		Color DL_Ambient = m_DirectionalLight->GetAmbientColor();
		Color DL_Diffuse = m_DirectionalLight->GetDiffuseColor();
		Color DL_Specular = m_DirectionalLight->GetSpecularColor();
		bool DL_IsEnabled = m_DirectionalLight->IsEnabled();
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, DLDirection), sizeof(LightingUniform::DLDirection), static_cast<void*>(&DL_Direction));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, DLAmbient), sizeof(LightingUniform::DLAmbient), static_cast<void*>(&DL_Ambient));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, DLDiffuse), sizeof(LightingUniform::DLDiffuse), static_cast<void*>(&DL_Diffuse));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, DLSpecular), sizeof(LightingUniform::DLSpecular), static_cast<void*>(&DL_Specular));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, DLIsEnabled), sizeof(LightingUniform::DLIsEnabled), static_cast<void*>(&DL_IsEnabled));

		Vector3 SL_Position = m_SpotLight->GetActor()->GetTransform()->GetPosition();
		Vector3 SL_Direction = m_SpotLight->GetActor()->GetTransform()->GetForward();
		Color SL_Ambient = m_SpotLight->GetAmbientColor();
		Color SL_Diffuse = m_SpotLight->GetDiffuseColor();
		Color SL_Specular = m_SpotLight->GetSpecularColor();
		float SL_InnerAngle = m_SpotLight->GetInnerAngle();
		float SL_OuterAngle = m_SpotLight->GetOuterAngle();
		float SL_Constant = m_SpotLight->GetConstant();
		float SL_Linear = m_SpotLight->GetLinear();
		float SL_Quadratic = m_SpotLight->GetQuadratic();
		bool SL_IsEnabled = m_SpotLight->IsEnabled();
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLPosition), sizeof(LightingUniform::SLPosition), static_cast<void*>(&SL_Position));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLDirection), sizeof(LightingUniform::SLDirection), static_cast<void*>(&SL_Direction));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLAmbient), sizeof(LightingUniform::SLAmbient), static_cast<void*>(&SL_Ambient));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLDiffuse), sizeof(LightingUniform::SLDiffuse), static_cast<void*>(&SL_Diffuse));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLSpecular), sizeof(LightingUniform::SLSpecular), static_cast<void*>(&SL_Specular));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLInnerAngle), sizeof(LightingUniform::SLInnerAngle), static_cast<void*>(&SL_InnerAngle));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLOuterAngle), sizeof(LightingUniform::SLOuterAngle), static_cast<void*>(&SL_OuterAngle));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLConstant), sizeof(LightingUniform::SLConstant), static_cast<void*>(&SL_Constant));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLLinear), sizeof(LightingUniform::SLLinear), static_cast<void*>(&SL_Linear));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLQuadratic), sizeof(LightingUniform::SLQuadratic), static_cast<void*>(&SL_Quadratic));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, SLIsEnabled), sizeof(LightingUniform::SLIsEnabled), static_cast<void*>(&SL_IsEnabled));

		Vector3 PL_Position1 = m_PointLights[0]->GetActor()->GetTransform()->GetPosition();
		Color PL_Ambient1 = m_PointLights[0]->GetAmbientColor();
		Color PL_Diffuse1 = m_PointLights[0]->GetDiffuseColor();
		Color PL_Specular1 = m_PointLights[0]->GetSpecularColor();
		float PL_Constant1 = m_PointLights[0]->GetConstant();
		float PL_Linear1 = m_PointLights[0]->GetLinear();
		float PL_Quadratic1 = m_PointLights[0]->GetQuadratic();
		bool PL_IsEnabled1 = m_PointLights[0]->IsEnabled();
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLPosition1), sizeof(LightingUniform::PLPosition1), static_cast<void*>(&PL_Position1));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLAmbient1), sizeof(LightingUniform::PLAmbient1), static_cast<void*>(&PL_Ambient1));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLDiffuse1), sizeof(LightingUniform::PLDiffuse1), static_cast<void*>(&PL_Diffuse1));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLSpecular1), sizeof(LightingUniform::PLSpecular1), static_cast<void*>(&PL_Specular1));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLConstant1), sizeof(LightingUniform::PLConstant1), static_cast<void*>(&PL_Constant1));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLLinear1), sizeof(LightingUniform::PLLinear1), static_cast<void*>(&PL_Linear1));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLQuadratic1), sizeof(LightingUniform::PLQuadratic1), static_cast<void*>(&PL_Quadratic1));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLIsEnabled1), sizeof(LightingUniform::PLIsEnabled1), static_cast<void*>(&PL_IsEnabled1));

		Vector3 PL_Position2 = m_PointLights[1]->GetActor()->GetTransform()->GetPosition();
		Color PL_Ambient2 = m_PointLights[1]->GetAmbientColor();
		Color PL_Diffuse2 = m_PointLights[1]->GetDiffuseColor();
		Color PL_Specular2 = m_PointLights[1]->GetSpecularColor();
		float PL_Constant2 = m_PointLights[1]->GetConstant();
		float PL_Linear2 = m_PointLights[1]->GetLinear();
		float PL_Quadratic2 = m_PointLights[1]->GetQuadratic();
		bool PL_IsEnabled2 = m_PointLights[1]->IsEnabled();
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLPosition2), sizeof(LightingUniform::PLPosition2), static_cast<void*>(&PL_Position2));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLAmbient2), sizeof(LightingUniform::PLAmbient2), static_cast<void*>(&PL_Ambient2));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLDiffuse2), sizeof(LightingUniform::PLDiffuse2), static_cast<void*>(&PL_Diffuse2));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLSpecular2), sizeof(LightingUniform::PLSpecular2), static_cast<void*>(&PL_Specular2));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLConstant2), sizeof(LightingUniform::PLConstant2), static_cast<void*>(&PL_Constant2));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLLinear2), sizeof(LightingUniform::PLLinear2), static_cast<void*>(&PL_Linear2));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLQuadratic2), sizeof(LightingUniform::PLQuadratic2), static_cast<void*>(&PL_Quadratic2));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLIsEnabled2), sizeof(LightingUniform::PLIsEnabled2), static_cast<void*>(&PL_IsEnabled2));

		Vector3 PL_Position3 = m_PointLights[2]->GetActor()->GetTransform()->GetPosition();
		Color PL_Ambient3 = m_PointLights[2]->GetAmbientColor();
		Color PL_Diffuse3 = m_PointLights[2]->GetDiffuseColor();
		Color PL_Specular3 = m_PointLights[2]->GetSpecularColor();
		float PL_Constant3 = m_PointLights[2]->GetConstant();
		float PL_Linear3 = m_PointLights[2]->GetLinear();
		float PL_Quadratic3 = m_PointLights[2]->GetQuadratic();
		bool PL_IsEnabled3 = m_PointLights[2]->IsEnabled();
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLPosition3), sizeof(LightingUniform::PLPosition3), static_cast<void*>(&PL_Position3));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLAmbient3), sizeof(LightingUniform::PLAmbient3), static_cast<void*>(&PL_Ambient3));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLDiffuse3), sizeof(LightingUniform::PLDiffuse3), static_cast<void*>(&PL_Diffuse3));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLSpecular3), sizeof(LightingUniform::PLSpecular3), static_cast<void*>(&PL_Specular3));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLConstant3), sizeof(LightingUniform::PLConstant3), static_cast<void*>(&PL_Constant3));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLLinear3), sizeof(LightingUniform::PLLinear3), static_cast<void*>(&PL_Linear3));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLQuadratic3), sizeof(LightingUniform::PLQuadratic3), static_cast<void*>(&PL_Quadratic3));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLIsEnabled3), sizeof(LightingUniform::PLIsEnabled3), static_cast<void*>(&PL_IsEnabled3));

		Vector3 PL_Position4 = m_PointLights[3]->GetActor()->GetTransform()->GetPosition();
		Color PL_Ambient4 = m_PointLights[3]->GetAmbientColor();
		Color PL_Diffuse4 = m_PointLights[3]->GetDiffuseColor();
		Color PL_Specular4 = m_PointLights[3]->GetSpecularColor();
		float PL_Constant4 = m_PointLights[3]->GetConstant();
		float PL_Linear4 = m_PointLights[3]->GetLinear();
		float PL_Quadratic4 = m_PointLights[3]->GetQuadratic();
		bool PL_IsEnabled4 = m_PointLights[3]->IsEnabled();
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLPosition4), sizeof(LightingUniform::PLPosition4), static_cast<void*>(&PL_Position4));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLAmbient4), sizeof(LightingUniform::PLAmbient4), static_cast<void*>(&PL_Ambient4));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLDiffuse4), sizeof(LightingUniform::PLDiffuse4), static_cast<void*>(&PL_Diffuse4));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLSpecular4), sizeof(LightingUniform::PLSpecular4), static_cast<void*>(&PL_Specular4));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLConstant4), sizeof(LightingUniform::PLConstant4), static_cast<void*>(&PL_Constant4));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLLinear4), sizeof(LightingUniform::PLLinear4), static_cast<void*>(&PL_Linear4));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLQuadratic4), sizeof(LightingUniform::PLQuadratic4), static_cast<void*>(&PL_Quadratic4));
		m_LightUniformBuffer->UpdateBuffer(offsetof(LightingUniform, PLIsEnabled4), sizeof(LightingUniform::PLIsEnabled4), static_cast<void*>(&PL_IsEnabled4));
	}

}