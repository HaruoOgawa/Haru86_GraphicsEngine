#pragma once

class BaseApp
{
	virtual void Start() const = 0;
	virtual void Update() const = 0;
	virtual void Timeline(class TimelineObject* timelineObj) const = 0;
};

