#pragma once
#include "GraphicsEngine/Component/Component.h"

class Object;

namespace component {
	class ARendererComponent :
		public Component
	{
	public:
		ARendererComponent(Object* o);
		~ARendererComponent();

		virtual void Update() override =0;
		virtual void Draw() = 0;
		virtual void ProcessInput(const SDL_Event& e) override = 0;

	protected:

	};
}