#pragma once
#include "../../../GraphicsEngine/Game/Game.h"
#include "../../../GraphicsEngine/App/BaseApp/BaseApp.h"
#include "../../../GraphicsEngine/Graphics/Mesh.h"
#include <vector>

class DemoApp
	: public BaseApp
{
public:
	DemoApp();
	~DemoApp();
	void Start()  override;
	void Update()  override;
	void Draw() override;
	void Timeline(class TimelineObject* timelineObj)  override;
private:
	
};

