#pragma once
#include <memory>

class BaseApp
{
private:
	friend class Game;
	friend class GameRenderer;
	virtual void Start()  = 0;
	virtual void Update()  = 0;
	virtual void Draw()  = 0;
	virtual void Timeline(std::shared_ptr<class TimelineObject> timelineObj)  = 0;
};

