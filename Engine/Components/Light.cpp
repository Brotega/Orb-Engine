#include "Light.h"
#include "../Actors/Actor.h"
#include "../Components/Transform.h"

namespace OrbEngine
{
	//-----------------Abstract Light-----------------
	Light::Light() :
		Component(),
		m_AmbientColor(Color::White), m_DiffuseColor(Color::White), m_SpecularColor(Color::White)
	{

	}

	Light::Light(const Color& ambientColor, const Color& diffuseColor, const Color& specularColor) :
		Component(),
		m_AmbientColor(ambientColor), m_DiffuseColor(diffuseColor), m_SpecularColor(specularColor)
	{

	}

	Light::~Light()
	{

	}
	//-----------------Abstract Light-----------------

	//-----------------Directional Light--------------
	DirectionalLight::DirectionalLight() : Light()
	{

	}

	DirectionalLight::~DirectionalLight()
	{

	}

	Vector3 DirectionalLight::GetDirection() const
	{
		return m_Actor->GetTransform()->GetForward();
	}
	//-----------------Directional Light--------------

	//-----------------Point Light--------------------
	PointLight::PointLight() : Light(),
		m_Constant(1.0f), m_Linear(0.4f), m_Quadratic(0.1f)
	{

	}

	PointLight::~PointLight()
	{

	}

	Vector3 PointLight::GetPosition() const
	{
		return m_Actor->GetTransform()->GetPosition();
	}
	//-----------------Point Light--------------------

	//-----------------Spot Light---------------------
	SpotLight::SpotLight() : Light(),
		m_InnerAngle(45.0f), m_OuterAngle(50.0f),
		m_Constant(1.0f), m_Linear(0.4f), m_Quadratic(0.1f)
	{

	}

	SpotLight::~SpotLight()
	{

	}
	//-----------------Spot Light---------------------
}