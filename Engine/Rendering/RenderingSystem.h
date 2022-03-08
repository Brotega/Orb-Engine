#pragma once

#include <vector>

namespace OrbEngine
{
	/* Forward declarations */
	class Application;
	class Camera;
	class CoordinateSystem;
	class Material;
	class MeshRenderer;
	class Skybox;
	class UniformBuffer;

	class RenderingSystem
	{
	public:
		/* Constructors/destructor */
		RenderingSystem(Application* application);
		~RenderingSystem();

		/*----------Enums----------*/
		enum class CompareFunction
		{
			ALWAYS,
			NEVER,
			LESS,
			EQUAL,
			LEQUAL,
			GREATER,
			NOTEQUAL,
			GEQUAL
		};

		enum class StencilAction
		{
			KEEP,
			ZERO,
			REPLACE,
			INCREASE,
			INCREASE_WRAP,
			DECREASE,
			DECREASE_WRAP,
			INVERT
		};

		enum class BlendFunction
		{
			ZERO,
			ONE,
			SRC_COLOR,
			ONE_MINUS_SRC_COLOR,
			DST_COLOR,
			ONE_MINUS_DST_COLOR,
			SRC_ALPHA,
			ONE_MINUS_SRC_ALPHA,
			DST_ALPHA,
			ONE_MINUS_DST_ALPHA,
			CONSTANT_COLOR,
			ONE_MINUS_CONSTANT_COLOR,
			CONSTANT_ALPHA,
			ONE_MINUS_CONSTANT_ALPHA
		};

		enum class BlendEquation
		{
			ADD,
			SUBTRACT,
			REVERSE_SUBTRACT,
			MIN,
			MAX
		};

		enum class CullFace
		{
			FRONT,
			BACK,
			FRONT_AND_BACK
		};

		enum class FrontFace
		{
			CLOCKWISE,
			COUNTER_CLOCKWISE
		};
		/*-------------------------*/

		/* Main functions - General */
		void AddCamera(Camera* camera) { m_Cameras.push_back(camera); }
		void AddMeshRenderer(MeshRenderer* meshRenderer);
		void DeleteCamera(Camera* camera) { m_Cameras.erase(std::find(m_Cameras.begin(), m_Cameras.end(), camera)); }
		void DeleteMeshRenderer(MeshRenderer* meshRenderer) { m_MeshRenderers.erase(std::find(m_MeshRenderers.begin(), m_MeshRenderers.end(), meshRenderer)); }
		void Render();
		void SetViewport(int width, int height) const;
		void SortMeshRenderersIfDirty();
		void UpdateCameraUniformMatrices(Camera* camera) const;

		/* Main functions - Rendering settings */
		void DrawBackgroundForCamera(Camera* camera) const;
		void EnableDepthTesting() const;
		void EnableStencilTesting() const;
		void EnableBlending() const;
		void EnableColorBufferClearFlag();
		void EnableDepthBufferClearFlag();
		void EnableStencilBufferClearFlag();
		void EnableDepthMask() const; // Enable writing to depth buffer
		void EnableFaceCulling() const;
		void DisableBlending() const;
		void DisableDepthTesting() const; // Disable writing to depth buffer
		void DisableStencilTesting() const;
		void DisableColorBufferClearFlag();
		void DisableDepthBufferClearFlag();
		void DisableStencilBufferClearFlag();
		void DisableDepthMask() const;
		void SetDepthFunction(const CompareFunction& compareFunction) const;
		void SetStencilMaskBit(unsigned int mask) const;
		void SetStencilFunction(const CompareFunction& compareFunction, int ref, unsigned int mask) const;
		void SetStencilOp(const StencilAction& sFail, const StencilAction& dpFail, const StencilAction& dpPass) const;		
		void SetBlendFunction(const BlendFunction& srcBlendFunction, const BlendFunction& dstBlendFunction) const;
		void SetBlendEquation(const BlendEquation& blendEquation) const;
		void SetCullFace(const CullFace& cullFace) const;
		void SetFrontFace(const FrontFace& frontFace) const;

		/* Setters */
		void SetShouldDrawCoordinateSystems(bool val) { m_ShouldDrawCoordinateSystems = val; }
		void SetSkyboxMaterial(Material* skyboxMaterial);
		void ToggleShouldDrawCoordinateSystems() { m_ShouldDrawCoordinateSystems = !m_ShouldDrawCoordinateSystems; }

		/* Getters */
		bool GetShouldDrawCoordinateSystems() const { return m_ShouldDrawCoordinateSystems; }
	
	private:
		Application* m_Application;
		CoordinateSystem* m_CoordinateSystem;
		Skybox* m_Skybox;
		UniformBuffer* m_UniformCameraMatrices;
		std::vector<Camera*> m_Cameras;
		std::vector<MeshRenderer*> m_MeshRenderers;
		bool m_ShouldDrawCoordinateSystems;
		bool m_MeshRenderersMarkedDirty;
		int m_GLClearFlags;

		unsigned int GetStencilOpFromEnum(const StencilAction& stencilAction) const;
		unsigned int GetBlendFuncFromEnum(const BlendFunction& blendFunc) const;
	};
}