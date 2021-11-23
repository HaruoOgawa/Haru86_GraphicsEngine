#pragma once
#include "../../Game/Game.h"
#include "../BaseApp/BaseApp.h"
#include "../../Graphics/VertexArray.h"
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

