#pragma once

#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "../Components/MeshRenderer.h"

#include <string> 
#include <vector>

namespace OrbEngine
{
	/* Forward declarations */
	class Application;
	class CoordinateSystem;
	class Component;
	class Transform;

	class Actor
	{
	public:
		/* Constructors/destructor */
		Actor(Application* application);
		Actor(Application* application, const std::string& actorName);
		~Actor();

		/* Main functions */
		template <typename T>
		T* GetComponent() const
		{
			for (size_t i = 0; i < m_Components.size(); ++i)
			{
				if (dynamic_cast<T*>(m_Components[i])) return (T*)m_Components[i];
			}

			return nullptr;
		}

		template <typename T>
		T* AddComponent(T* component) 
		{ 
			if (dynamic_cast<Component*>(component))
			{
				m_Components.push_back(component);

				// Only upcast to Component to set the actor to this
				Component* comp = (Component*)component;
				comp->SetActor(this);

				return component;
			}
			else return nullptr;
		}
		void DeleteComponent(Component* component) { m_Components.erase(std::find(m_Components.begin(), m_Components.end(), component)); }

		/* Virtual functions */
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);

		/* Setters */
		void SetParent(Transform* parent) { m_Parent = parent; }
		void SetEnabled(bool val) { m_IsEnabled = val; }

		/* Getters */
		Application* GetApplication() const { return m_Application; }
		std::vector<Transform*> GetChildren() const { return m_Children; }
		std::string GetName() const { return m_ActorName; }
		Transform* GetParent() const { return m_Parent; }
		Transform* GetTransform() const { return m_Transform; }
		bool IsEnabled() const { return m_IsEnabled; }

	protected:
		/* Components */
		Transform* m_Transform;
		std::vector<Component*> m_Components;
		/*------------*/

		Application* m_Application;
		Transform* m_Parent;
		std::vector<Transform*> m_Children;
		std::string m_ActorName;
		bool m_IsEnabled;
	};
}