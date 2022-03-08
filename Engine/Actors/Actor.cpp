#include "Actor.h"
#include "../Application/Application.h"
#include "../Components/Transform.h"
#include "../Debugging/CoordinateSystem.h"

namespace OrbEngine
{
	Actor::Actor(Application* application) :
		m_Transform(new Transform()), m_Application(application),
		m_ActorName("Actor"), m_IsEnabled(true), m_Parent(nullptr)
	{
		m_Application->AddActor(this);
		m_Transform->SetActor(this);
	}

	Actor::Actor(Application* application, const std::string& actorName) :
		m_Transform(new Transform()), m_Application(application),
		m_ActorName(actorName), m_IsEnabled(true), m_Parent(nullptr)
	{
		m_Application->AddActor(this);
		m_Transform->SetActor(this);
	}

	Actor::~Actor()
	{
		delete m_Transform;
	}

	void Actor::Update(float deltaTime)
	{

	}

	void Actor::LateUpdate(float deltaTime)
	{

	}
}