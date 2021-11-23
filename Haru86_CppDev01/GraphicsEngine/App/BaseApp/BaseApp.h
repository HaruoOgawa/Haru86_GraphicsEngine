#pragma once

class BaseApp
{
private:
	friend class Game;
	virtual void Start()  = 0;
	virtual void Update()  = 0;
	virtual void Timeline(class TimelineObject* timelineObj)  = 0;
};

