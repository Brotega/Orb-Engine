#pragma once
#include "Component.h"
#include "../Math/Math.h"
#include "../Rendering/Color.h"

namespace OrbEngine
{
	/* Forward declarations */

	class Light : public Component
	{
	public:
		/* Constructors/destructor */
		Light();
		Light(const Color& ambientColor, const Color& diffuseColor, const Color& specularColor);
		~Light();

		/* Setters */
		void SetActor(Actor* actor) { m_Actor = actor; }
		void SetAmbientColor(const Color& color) { m_AmbientColor = color; }
		void SetDiffuseColor(const Color& color) { m_DiffuseColor = color; }
		void SetSpecularColor(const Color& color) { m_SpecularColor = color; }

		/* Getters */
		Color GetAmbientColor() const { return m_AmbientColor; }
		Color GetDiffuseColor() const { return m_DiffuseColor; }
		Color GetSpecularColor() const { return m_SpecularColor; }

	protected:

		Color m_AmbientColor;
		Color m_DiffuseColor;
		Color m_SpecularColor;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight();
		~DirectionalLight();

		Vector3 GetDirection() const;

	private:
	};

	class PointLight : public Light
	{
	public:
		PointLight();
		~PointLight();

		/* Setters */
		void SetAttenutation(float constant, float linear, float quadratic) { m_Constant = constant; m_Linear = linear; m_Quadratic = quadratic; }
		void SetConstant(float constant) { m_Constant = constant; }
		void SetLinear(float linear) { m_Linear = linear; }
		void SetQuadratic(float quadratic) { m_Quadratic = quadratic; }

		/* Getters */
		float GetConstant() const { return m_Constant; }
		float GetLinear() const { return m_Linear; }
		float GetQuadratic() const { return m_Quadratic; }
		Vector3 GetPosition() const;

	private:

		/* Attenuation constants */
		float m_Constant;
		float m_Linear;
		float m_Quadratic;
	};

	class SpotLight : public Light
	{
	public:
		SpotLight();
		~SpotLight();

		/* Setters */
		void SetInnerAngle(float innerAngle) { m_InnerAngle = innerAngle; }
		void SetOuterAngle(float outerAngle) { m_OuterAngle = outerAngle; }
		void SetConstant(float constant) { m_Constant = constant; }
		void SetLinear(float linear) { m_Linear = linear; }
		void SetQuadratic(float quadratic) { m_Quadratic = quadratic; }

		/* Getters */
		float GetInnerAngle() const { return m_InnerAngle; }
		float GetOuterAngle() const { return m_OuterAngle; }
		float GetConstant() const { return m_Constant; }
		float GetLinear() const { return m_Linear; }
		float GetQuadratic() const { return m_Quadratic; }

	private:
		/* In degrees */
		float m_InnerAngle;
		float m_OuterAngle;

		/* Falloff over distance constants */
		float m_Constant;
		float m_Linear;
		float m_Quadratic;
	};
}