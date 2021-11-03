#pragma once

class BaseApp
{
	virtual void Start()  = 0;
	virtual void Update()  = 0;
	virtual void Timeline(class TimelineObject* timelineObj)  = 0;
};

