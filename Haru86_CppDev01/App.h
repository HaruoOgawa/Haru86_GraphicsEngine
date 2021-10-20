#pragma once
#include "./Game.h"
#include "./BaseApp.h"
#include "./VertexArray.h"

class App
	: public BaseApp
{
public:
	App();
	~App();
	void Start() const override;
	void Update() const override;
	void Timeline(class TimelineObject* timelineObj) const override;
private:
};

