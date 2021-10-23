#pragma once
#include "Object.h"
#include <functional>

class TimelineObject :
    public Object
{
public:
    TimelineObject();
    ~TimelineObject();
    void AddActivationClip(class GameObject* obj,float startTime,float endTime);
    void AddCustomClip(class GameObject* obj,float startTime,float endTime,std::function<void(void)> callback);
    friend Game;
    friend class UIComponent;
private:
    class TimelineComponent* timelineComponent;
    void Initialize();
};

