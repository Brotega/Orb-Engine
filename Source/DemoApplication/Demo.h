#pragma once
#include "../../Engine/Application/Application.h"

namespace OrbEngine
{
	/* Forward declarations */
	class FreeMoveCamera;

	/* FreeMoveCamera */
	class Demo : public Application
	{
	public:
		/* Constructors/destructors */
		Demo(int screenWidth, int screenHeight, float frameRate);
		~Demo();

	private:
		FreeMoveCamera* m_FreeMoveCamera;

		/* Internal override functions */
		bool Initialize() override;
		void ProcessInput() override;
		void Update(float deltaTime) override;
		void LateUpdate(float deltaTime) override;
		void RenderFrame() override;
		bool LoadScene() override; // May make this one public in the future
	};
}