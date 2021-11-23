#pragma once
#include "../../../GraphicsEngine/Game/Game.h"
#include "../../../GraphicsEngine/App/BaseApp/BaseApp.h"
#include "../../../GraphicsEngine/Graphics/Mesh.h"
#include <vector>

class App
	: public BaseApp
{
public:
	App();
	~App();
	void Start()  override;
	void Update()  override;
	void Timeline(class TimelineObject* timelineObj)  override;
private:
	
};

