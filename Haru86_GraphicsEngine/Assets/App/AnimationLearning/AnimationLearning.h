#pragma once
#include "GraphicsEngine/App/BaseApp/BaseApp.h"
class AnimationLearning :
    public BaseApp
{
public:
	AnimationLearning() = default;
	~AnimationLearning() = default;

	virtual void Start() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Timeline(class TimelineObject* timelineObj) override;
};

