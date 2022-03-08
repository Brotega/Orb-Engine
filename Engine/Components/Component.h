#pragma once

namespace OrbEngine
{
	/* Forward declarations */
	class Actor;

	class Component
	{
	public:
		/* Constructors/destructor */
		Component();
		virtual ~Component();

		/* Main functions */
		bool IsEnabled() const { return m_IsEnabled; }

		/* Setters */
		void SetActor(Actor* actor) { m_Actor = actor; }
		void SetEnabled(bool val) { m_IsEnabled = val; }

		/* Getters */
		Actor* GetActor() const { return m_Actor; }

	protected:
		Actor* m_Actor;
		bool m_IsEnabled;
	};
}