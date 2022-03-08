#include "Demo.h"

#include "../../Engine/Actors/Actor.h"
#include "../../Engine/Actors/Testing/FreeMoveCamera.h"
#include "../../Engine/AssetManager/AssetManager.h"
#include "../../Engine/Components/Camera.h"
#include "../../Engine/Components/Light.h"
#include "../../Engine/Components/MeshRenderer.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Debugging/CoordinateSystem.h"
#include "../../Engine/Debugging/Grid.h"
#include "../../Engine/Input/InputSystem.h"
#include "../../Engine/Math/Math.h"
#include "../../Engine/Rendering/Color.h"
#include "../../Engine/Rendering/CubeMap.h"
#include "../../Engine/Rendering/Material.h"
#include "../../Engine/Rendering/Mesh.h"
#include "../../Engine/Rendering/PostProcessingEffect.h"
#include "../../Engine/Rendering/RenderingSystem.h"
#include "../../Engine/Rendering/Shader.h"
#include "../../Engine/Rendering/Skybox.h"
#include "../../Engine/Rendering/Texture2D.h"
#include "../../Engine/Rendering/Buffer/UniformBuffer.h"

#include <string>
#include <fstream>

#include <SDL2/SDL.h>

namespace OrbEngine
{
	Demo::Demo(int screenWidth, int screenHeight, float frameRate) :
		Application(screenWidth, screenHeight, frameRate, "Demo"), m_FreeMoveCamera(nullptr)
	{

	}

	Demo::~Demo()
	{

	}

	bool Demo::Initialize()
	{
		m_InputSystem->DisableCursor();
		return true;
	}

	bool Demo::LoadScene()
	{
		Texture2D* brickTexture4096 = new Texture2D();
		if (brickTexture4096->Load("Brick_4096/Brick_BaseColor.png", TextureType::DEFAULT))
		{
			m_AssetManager->StoreTexture("Brick_D_4096", brickTexture4096);
		}

		CubeMap* skyCubeMap = new CubeMap();
		std::vector<std::string> skyFiles
		{
			"Cloudy-Crown/CloudyCrown_Midday_Back.png",
			"Cloudy-Crown/CloudyCrown_Midday_Left.png",
			"Cloudy-Crown/CloudyCrown_Midday_Up.png",
			"Cloudy-Crown/CloudyCrown_Midday_Down.png",
			"Cloudy-Crown/CloudyCrown_Midday_Front.png",
			"Cloudy-Crown/CloudyCrown_Midday_Back.png",
		};
		if (skyCubeMap->Load(skyFiles))
		{
			m_AssetManager->StoreCubeMap("CubeMap_Sky", skyCubeMap);
		}

		std::string modelDirectory = m_AssetManager->GetModelRootDirectory();
		Mesh* cubeMesh = new Mesh();
		if (cubeMesh->Load(modelDirectory + "Cube.fbx"))
		{
			m_AssetManager->StoreMesh("Mesh", cubeMesh);
		}

		/* Free Moving Camera Actor */
		m_FreeMoveCamera = new FreeMoveCamera(this);
		m_FreeMoveCamera->AddComponent(m_MainCamera);
		m_FreeMoveCamera->GetTransform()->SetPosition(Vector3(0.0f, 1.0f, -8.0f));
		m_RenderingSystem->AddCamera(m_MainCamera);
		m_MainCamera->SetBackgroundType(Camera::BackgroundType::SKYBOX);
		/*-------------------------*/

		/* HQ Brick Material */
		Material* hqBrickMaterial = new Material();
		m_AssetManager->StoreMaterial("TEX_HQBrick", hqBrickMaterial);
		hqBrickMaterial->SetShader(m_AssetManager->GetShader("Lit"));
		hqBrickMaterial->SetTexture2D("materialProperty.Diffuse", brickTexture4096);
		hqBrickMaterial->SetTexture2D("materialProperty.Specular", m_AssetManager->GetTexture("Black"));
		hqBrickMaterial->SetFloat("materialProperty.Shininess", 32.0f);
		/*-------------------*/

		/* HQ Brick MeshRenderer*/
		MeshRenderer* hqBrickMeshRenderer = new MeshRenderer();
		hqBrickMeshRenderer->SetMesh(cubeMesh);
		hqBrickMeshRenderer->SetMaterial(hqBrickMaterial);
		m_RenderingSystem->AddMeshRenderer(hqBrickMeshRenderer);
		/*---------------------*/

		/* HQ Brick Model Actor */
		Actor* highqualityBrickModel = new Actor(this);
		highqualityBrickModel->AddComponent(hqBrickMeshRenderer);
		highqualityBrickModel->GetTransform()->SetPosition(Vector3::Left * 2.6f);
		highqualityBrickModel->GetTransform()->SetScale(5.0f * Vector3::One);
		highqualityBrickModel->GetTransform()->UpdateLocalToWorldMatrix();
		/*---------------------*/

		/* Directional Light Settings */
		m_DirectionalLight->GetActor()->GetTransform()->SetRotation(Quaternion::AxisAngle(Vector3::Left, Math::Deg2Rad * 90.0f));
		m_DirectionalLight->GetActor()->GetTransform()->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
		m_DirectionalLight->SetAmbientColor(0.5f * Color::White);
		m_DirectionalLight->SetDiffuseColor(0.5f * Color::White);
		m_DirectionalLight->SetSpecularColor(0.4f * Color::White);
		/*----------------------------*/

		/* Set Sky box */
		Material* skyboxMaterial = new Material();
		skyboxMaterial->SetShader(m_AssetManager->GetShader("Skybox"));
		skyboxMaterial->SetCubeMap("materialProperty.Skybox", skyCubeMap);
		m_RenderingSystem->SetSkyboxMaterial(skyboxMaterial);
		/*-------------*/

		return true;
	}

	void Demo::ProcessInput()
	{

		if (!m_InputSystem->GetMouseState().m_IsCursorEnabled)
		{
			if (m_InputSystem->GetKey(m_InputSystem->KEYBOARD_W)) m_FreeMoveCamera->MoveForward();
			else m_FreeMoveCamera->StopForward();
			if (m_InputSystem->GetKey(m_InputSystem->KEYBOARD_A)) m_FreeMoveCamera->MoveLeft();
			else m_FreeMoveCamera->StopLeft();
			if (m_InputSystem->GetKey(m_InputSystem->KEYBOARD_D)) m_FreeMoveCamera->MoveRight();
			else m_FreeMoveCamera->StopRight();
			if (m_InputSystem->GetKey(m_InputSystem->KEYBOARD_S)) m_FreeMoveCamera->MoveBackward();
			else m_FreeMoveCamera->StopBackward();
			if (m_InputSystem->GetKey(m_InputSystem->KEYBOARD_Q)) m_FreeMoveCamera->MoveUp();
			else m_FreeMoveCamera->StopUp();
			if (m_InputSystem->GetKey(m_InputSystem->KEYBOARD_E)) m_FreeMoveCamera->MoveDown();
			else m_FreeMoveCamera->StopDown();
			if (m_InputSystem->GetKey(m_InputSystem->KEYBOARD_LSHIFT)) m_FreeMoveCamera->SpeedUp();
			else m_FreeMoveCamera->ResetSpeed();
			m_FreeMoveCamera->RotateLookDirection(m_InputSystem->GetDeltaMousePositionIfMouseEnabled());
			if (m_InputSystem->GetKeyDown(m_InputSystem->KEYBOARD_F1))
			{
				if (m_RenderingSystem->GetShouldDrawCoordinateSystems() == true)
				{
					m_RenderingSystem->SetShouldDrawCoordinateSystems(false);
				}
				else
				{
					m_RenderingSystem->SetShouldDrawCoordinateSystems(true);
				}
			}
		}
	}

	void Demo::Update(float deltaTime)
	{
		for (size_t i = 0; i < m_Actors.size(); i++)
		{
			m_Actors[i]->Update(deltaTime);
		}
	}

	void Demo::LateUpdate(float deltaTime)
	{

		for (size_t i = 0; i < m_Actors.size(); i++)
		{
			m_Actors[i]->LateUpdate(deltaTime);
		}
	}

	void Demo::RenderFrame()
	{
		m_RenderingSystem->Render();
	}
}