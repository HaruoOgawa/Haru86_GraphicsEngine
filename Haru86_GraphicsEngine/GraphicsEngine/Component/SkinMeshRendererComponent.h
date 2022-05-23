#pragma once
#include "ARendererComponent.h"

class Object* o;

namespace component {
	class SkinMeshRendererComponent :
		public ARendererComponent
	{
	public:
		SkinMeshRendererComponent(Object* o);
		~SkinMeshRendererComponent();

		virtual void Update() override;
		virtual void Draw() override;
		virtual void ProcessInput(const SDL_Event& e) override;
	};
}