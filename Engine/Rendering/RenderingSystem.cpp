#include "RenderingSystem.h"
#include "../Actors/Actor.h"
#include "../Application/Application.h"
#include "../AssetManager/AssetManager.h"
#include "../Components/Camera.h"
#include "../Components/MeshRenderer.h"
#include "../Debugging/CoordinateSystem.h"
#include "../Rendering/Buffer/UniformBuffer.h"
#include "../Rendering/Material.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Skybox.h"

#include <glad/glad.h>

#include <algorithm>

namespace OrbEngine
{
	RenderingSystem::RenderingSystem(Application* application) :
		m_Application(application), m_UniformCameraMatrices(nullptr),
		m_CoordinateSystem(nullptr), m_MeshRenderersMarkedDirty(false),
		m_ShouldDrawCoordinateSystems(false), m_Skybox(nullptr),
		m_GLClearFlags(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)
	{
		m_CoordinateSystem = new CoordinateSystem();
		m_CoordinateSystem->SetShader(m_Application->GetAssetManager()->GetShader("Debug"));
		m_UniformCameraMatrices = new UniformBuffer(0, 148);

		glViewport(0, 0, m_Application->GetScreenWidth(), m_Application->GetScreenHeight());

		EnableDepthTesting();

		m_Skybox = new Skybox();
	}

	RenderingSystem::~RenderingSystem()
	{
		delete m_Skybox;
		delete m_UniformCameraMatrices;
		delete m_CoordinateSystem;

		for (size_t i = 0; i < m_MeshRenderers.size(); ++i)
		{
			delete m_MeshRenderers[i];
		}
		m_MeshRenderers.clear();
	}

	void RenderingSystem::AddMeshRenderer(MeshRenderer* meshRenderer)
	{
		m_MeshRenderers.push_back(meshRenderer);
		m_MeshRenderersMarkedDirty = true;
	}

	void RenderingSystem::Render()
	{
		SortMeshRenderersIfDirty(); // Set the draw order for all mesh/materials

		for (Camera* camera : m_Cameras)
		{
			UpdateCameraUniformMatrices(camera);

			glClear(m_GLClearFlags);
			DrawBackgroundForCamera(camera);

			for (MeshRenderer* meshRenderer : m_MeshRenderers)
			{
				Actor* actor = meshRenderer->GetActor();
				Mesh* mesh = meshRenderer->GetMesh();
				Material* material = meshRenderer->GetMaterial();
				Matrix4x4 model = actor->GetTransform()->GetLocalToWorldMatrix();

				if (mesh == nullptr || material == nullptr) continue;

				material->UseShader();
				material->SetMatrix4x4("model", model);
				material->SetProperties();
				mesh->Draw();
			}

			if (m_ShouldDrawCoordinateSystems)
			{
				std::vector<Actor*> actors = m_Application->GetActors();

				DisableDepthTesting();
				for (Actor* actor : actors)
				{
					if (actor->IsEnabled())
					{
						m_CoordinateSystem->SetPosition(actor->GetTransform()->GetPosition());
						m_CoordinateSystem->SetScale(actor->GetTransform()->GetScale());
						m_CoordinateSystem->SetRotation(actor->GetTransform()->GetRotationQuaternion());
						m_CoordinateSystem->UpdateAxis();
						m_CoordinateSystem->Draw();
					}
				}
				EnableDepthTesting();
			}
		}
	}

	void RenderingSystem::SetViewport(int width, int height) const
	{
		glViewport(0, 0, width, height);
	}

	void RenderingSystem::SortMeshRenderersIfDirty()
	{
		if (m_MeshRenderersMarkedDirty)
		{
			std::sort(m_MeshRenderers.begin(), m_MeshRenderers.end(), MeshRendererLessThanComparator());
			m_MeshRenderersMarkedDirty = false;
		}
	}

	void RenderingSystem::UpdateCameraUniformMatrices(Camera* camera) const
	{
		Matrix4x4 view = camera->GetViewMatrix();
		Matrix4x4 projection = camera->GetProjectionMatrix();
		Vector3 position = camera->GetActor()->GetTransform()->GetPosition();
		float zNear = camera->GetZNear();
		float zFar = camera->GetZFar();

		m_UniformCameraMatrices->UpdateBuffer(offsetof(CameraUniform, View), sizeof(CameraUniform::View), static_cast<const void*>(&view));
		m_UniformCameraMatrices->UpdateBuffer(offsetof(CameraUniform, Projection), sizeof(CameraUniform::Projection), static_cast<const void*>(&projection));
		m_UniformCameraMatrices->UpdateBuffer(offsetof(CameraUniform, Position), sizeof(CameraUniform::Position), static_cast<const void*>(&position));
		m_UniformCameraMatrices->UpdateBuffer(offsetof(CameraUniform, ZNear), sizeof(CameraUniform::ZNear), static_cast<const void*>(&zNear));
		m_UniformCameraMatrices->UpdateBuffer(offsetof(CameraUniform, ZFar), sizeof(CameraUniform::ZFar), static_cast<const void*>(&zFar));
	}

	void RenderingSystem::DrawBackgroundForCamera(Camera* camera) const
	{
		Camera::BackgroundType backgroundType = camera->GetBackgroundType();

		switch (backgroundType)
		{
		case Camera::BackgroundType::SOLID_COLOR:
			glClearColor(camera->GetBackgroundColor().r, 
						camera->GetBackgroundColor().g, 
						camera->GetBackgroundColor().b, 1.0);
			break;
		case Camera::BackgroundType::SKYBOX:
			DisableDepthTesting();
			m_Skybox->Draw();
			EnableDepthTesting();
			break;
		}
	}

	void RenderingSystem::EnableDepthTesting() const
	{
		glEnable(GL_DEPTH_TEST);
	}

	void RenderingSystem::EnableStencilTesting() const
	{
		glEnable(GL_STENCIL_TEST);
	}

	void RenderingSystem::EnableBlending() const
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderingSystem::EnableColorBufferClearFlag()
	{
		m_GLClearFlags |= GL_COLOR_BUFFER_BIT;
	}

	void RenderingSystem::EnableDepthBufferClearFlag()
	{
		m_GLClearFlags |= GL_DEPTH_BUFFER_BIT;
	}

	void RenderingSystem::EnableStencilBufferClearFlag()
	{
		m_GLClearFlags |= GL_STENCIL_BUFFER_BIT;
	}

	void RenderingSystem::EnableDepthMask() const
	{
		glDepthMask(GL_TRUE);
	}

	void RenderingSystem::EnableFaceCulling() const
	{
		glEnable(GL_CULL_FACE);
	}


	void RenderingSystem::DisableDepthTesting() const
	{
		glDisable(GL_DEPTH_TEST);
	}

	void RenderingSystem::DisableStencilTesting() const
	{
		glDisable(GL_STENCIL_TEST);
	}

	void RenderingSystem::DisableBlending() const
	{
		glDisable(GL_BLEND);
	}

	void RenderingSystem::DisableColorBufferClearFlag()
	{
		m_GLClearFlags &= ~GL_COLOR_BUFFER_BIT;
	}

	void RenderingSystem::DisableDepthBufferClearFlag()
	{
		m_GLClearFlags &= ~GL_DEPTH_BUFFER_BIT;
	}

	void RenderingSystem::DisableStencilBufferClearFlag()
	{
		m_GLClearFlags &= ~GL_STENCIL_BUFFER_BIT;
	}

	void RenderingSystem::DisableDepthMask() const
	{
		glDepthMask(GL_FALSE);
	}

	void RenderingSystem::SetDepthFunction(const CompareFunction& compareFunction) const
	{
		GLenum func = GL_ALWAYS;
		switch (compareFunction)
		{
		case CompareFunction::ALWAYS:
			func = GL_ALWAYS;
			break;

		case CompareFunction::NEVER:
			func = GL_NEVER;
			break;

		case CompareFunction::LESS:
			func = GL_LESS;
			break;

		case CompareFunction::EQUAL:
			func = GL_EQUAL;
			break;

		case CompareFunction::LEQUAL:
			func = GL_LEQUAL;
			break;

		case CompareFunction::GREATER:
			func = GL_GREATER;
			break;

		case CompareFunction::NOTEQUAL:
			func = GL_NOTEQUAL;
			break;

		case CompareFunction::GEQUAL:
			func = GL_GEQUAL;
			break;
		}

		glDepthFunc(func);

	}

	void RenderingSystem::SetStencilMaskBit(unsigned int mask) const
	{
		glStencilMask(mask);
	}

	void RenderingSystem::SetStencilFunction(const CompareFunction& compareFunction, int ref, unsigned int mask) const
	{
		GLenum func = GL_ALWAYS;
		switch (compareFunction)
		{
		case CompareFunction::ALWAYS:
			func = GL_ALWAYS;
			break;

		case CompareFunction::NEVER:
			func = GL_NEVER;
			break;

		case CompareFunction::LESS:
			func = GL_LESS;
			break;

		case CompareFunction::EQUAL:
			func = GL_EQUAL;
			break;

		case CompareFunction::LEQUAL:
			func = GL_LEQUAL;
			break;

		case CompareFunction::GREATER:
			func = GL_GREATER;
			break;

		case CompareFunction::NOTEQUAL:
			func = GL_NOTEQUAL;
			break;

		case CompareFunction::GEQUAL:
			func = GL_GEQUAL;
			break;
		}

		glStencilFunc(func, ref, mask);
	}

	void RenderingSystem::SetStencilOp(const StencilAction& sFail, const StencilAction& dpFail, const StencilAction& dpPass) const
	{
		glStencilOp(GetStencilOpFromEnum(sFail), GetStencilOpFromEnum(dpFail), GetStencilOpFromEnum(dpPass));
	}

	unsigned int RenderingSystem::GetStencilOpFromEnum(const StencilAction& stencilAction) const
	{
		GLenum op = GL_KEEP;

		switch (stencilAction)
		{

		case StencilAction::KEEP:
			op = GL_KEEP;
			break;

		case StencilAction::ZERO:
			op = GL_ZERO;
			break;

		case StencilAction::REPLACE:
			op = GL_REPLACE;
			break;

		case StencilAction::INCREASE:
			op = GL_INCR;
			break;

		case StencilAction::INCREASE_WRAP:
			op = GL_INCR_WRAP;
			break;

		case StencilAction::DECREASE:
			op = GL_DECR;
			break;

		case StencilAction::DECREASE_WRAP:
			op = GL_DECR_WRAP;
			break;

		case StencilAction::INVERT:
			op = GL_INVERT;
			break;
		}

		return op;
	}

	void RenderingSystem::SetBlendFunction(const BlendFunction& srcBlendFunction, const BlendFunction& dstBlendFunction) const
	{
		glBlendFunc(GetBlendFuncFromEnum(srcBlendFunction), GetBlendFuncFromEnum(dstBlendFunction));
	}

	unsigned int RenderingSystem::GetBlendFuncFromEnum(const BlendFunction& blendFunc) const
	{
		GLenum blend = GL_ZERO;

		switch (blendFunc)
		{

		case BlendFunction::ZERO:
			blend = GL_ZERO;
			break;

		case BlendFunction::ONE:
			blend = GL_ONE;
			break;

		case BlendFunction::SRC_COLOR:
			blend = GL_SRC_COLOR;
			break;

		case BlendFunction::ONE_MINUS_SRC_COLOR:
			blend = GL_ONE_MINUS_SRC_COLOR;
			break;

		case BlendFunction::DST_COLOR:
			blend = GL_DST_COLOR;
			break;

		case BlendFunction::ONE_MINUS_DST_COLOR:
			blend = GL_ONE_MINUS_DST_COLOR;
			break;

		case BlendFunction::SRC_ALPHA:
			blend = GL_SRC_ALPHA;
			break;

		case BlendFunction::ONE_MINUS_SRC_ALPHA:
			blend = GL_ONE_MINUS_SRC_ALPHA;
			break;

		case BlendFunction::DST_ALPHA:
			blend = GL_DST_ALPHA;
			break;

		case BlendFunction::ONE_MINUS_DST_ALPHA:
			blend = GL_ONE_MINUS_DST_ALPHA;
			break;

		case BlendFunction::CONSTANT_COLOR:
			blend = GL_COLOR;
			break;

		case BlendFunction::ONE_MINUS_CONSTANT_COLOR:
			blend = GL_ONE_MINUS_CONSTANT_COLOR;
			break;

		case BlendFunction::CONSTANT_ALPHA:
			blend = GL_CONSTANT_ALPHA;
			break;

		case BlendFunction::ONE_MINUS_CONSTANT_ALPHA:
			blend = GL_ONE_MINUS_CONSTANT_ALPHA;
			break;
		}

		return blend;
	}

	void RenderingSystem::SetBlendEquation(const BlendEquation& blendEquation) const
	{
		GLenum eq = GL_FUNC_ADD;

		switch (blendEquation)
		{
		case BlendEquation::ADD:
			eq = GL_FUNC_ADD;
			break;

		case BlendEquation::SUBTRACT:
			eq = GL_FUNC_SUBTRACT;
			break;

		case BlendEquation::REVERSE_SUBTRACT:
			eq = GL_FUNC_REVERSE_SUBTRACT;
			break;

		case BlendEquation::MIN:
			eq = GL_MIN;
			break;

		case BlendEquation::MAX:
			eq = GL_MAX;
			break;
		}

		glBlendEquation(eq);
	}

	void RenderingSystem::SetCullFace(const CullFace& cullFace) const
	{
		GLenum cull = GL_BACK;

		switch (cullFace)
		{
		case CullFace::FRONT:
			cull = GL_FRONT;
			break;

		case CullFace::BACK:
			cull = GL_BACK;
			break;

		case CullFace::FRONT_AND_BACK:
			cull = GL_FRONT_AND_BACK;
			break;
		}

		glCullFace(cull);
	}

	void RenderingSystem::SetFrontFace(const FrontFace& frontFace) const
	{
		GLenum front = GL_CCW;

		switch (frontFace)
		{
		case FrontFace::CLOCKWISE:
			front = GL_CW;
			break;

		case FrontFace::COUNTER_CLOCKWISE:
			front = GL_CCW;
			break;
		}

		glFrontFace(front);
	}

	void RenderingSystem::SetSkyboxMaterial(Material* skyboxMaterial)
	{
		m_Skybox->SetMaterial(skyboxMaterial);
	}
}