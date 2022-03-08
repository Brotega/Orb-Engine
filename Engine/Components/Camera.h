#pragma once
#include "Component.h"
#include "Transform.h"
#include "../Rendering/Color.h"

namespace OrbEngine
{
	/* Forward declarations */
	class Actor;
	class MeshRenderer;
	class UniformBuffer;

	/* Note to self - always attach Camera to an AActor */
	class Camera : public Component
	{
	public:
		/* Constructors/destructor */
		Camera();
		~Camera();

		/*----------Enums----------*/
		enum class ProjectionType
		{
			ORTHOGRAPHIC,
			PERSPECTIVE,
			UNDEFINED
		};

		enum class BackgroundType
		{
			SOLID_COLOR,
			SKYBOX
		};
		/*-------------------------*/

		/* Main functions */
		void SetAllCameraParameters(float zNear, float zFar, float width, float height);
		void SetAllCameraParameters(float zNear, float zFar, float width, float height, float fov);

		/* Setters */
		void SetFOV(float fov) { m_FOV = fov; }
		void SetBackgroundColor(const Color& color) { m_BackgroundColor = color; }
		void SetBackgroundType(BackgroundType cameraBackgroundType) { m_BackgroundType = cameraBackgroundType; }
		void SetProjectionType(ProjectionType cameraProjectionType) { m_CameraProjectionType = cameraProjectionType; }
		void SetWidth(float width) { m_Width = width; }
		void SetHeight(float height) { m_Height = height; }

		/* Getters */
		float GetFOV() const { return m_FOV; }
		float GetZNear() const { return m_ZNear; }
		float GetZFar() const { return m_ZFar; }
		Color GetBackgroundColor() const { return m_BackgroundColor; }
		BackgroundType GetBackgroundType() const { return m_BackgroundType; }
		Matrix4x4 GetViewMatrix() const;
		Matrix4x4 GetProjectionMatrix() const;
		Matrix4x4 GetOrthogonalMatrix() const;
		Matrix4x4 GetPerspectiveMatrix() const;

	private:
		ProjectionType m_CameraProjectionType;
		BackgroundType m_BackgroundType;
		Color m_BackgroundColor;

		float m_FOV;
		float m_ZNear;
		float m_ZFar;
		float m_Width;
		float m_Height;
	};
}