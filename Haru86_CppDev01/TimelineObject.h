#pragma once
#include "Object.h"
class TimelineObject :
    public Object
{
public:
    TimelineObject();
    ~TimelineObject();
    void AddActivationClip(class GameObject* obj,float startTime,float endTime);
    void AddAnimationClip(class GameObject* obj,float startTime,float endTime);
    friend Game;
private:
    class TimelineComponent* timelineComponent;
};

