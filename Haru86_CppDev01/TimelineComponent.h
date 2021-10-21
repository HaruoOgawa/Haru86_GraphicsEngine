#pragma once
#include "Component.h"
#include <vector>
#include <functional>

struct TimelineActivationClip
{
    class GameObject* gameObject;
    float startTime;
    float endTime;
    TimelineActivationClip(class GameObject* obj,float s,float e) {
        this->gameObject = obj;
        this->startTime = s;
        this->endTime = e;
    }
};

struct TimelineCustomClip
{
    class GameObject* gameObject;
    float startTime;
    float endTime;
    std::function<void(void)> callback;
    TimelineCustomClip(class GameObject* obj,float s,float e,std::function<void(void)> func) {
        this->gameObject = obj;
        this->startTime = s;
        this->endTime = e;
        this->callback = func;
    }
};

class TimelineComponent :
    public Component
{
public:
    TimelineComponent(class Object* o);
    ~TimelineComponent();
    void Update() override;
    void Initialize();
    void ComputeTimeline(float time);
    friend TimelineObject;
    float timeVal;
private:
    void InitializeActivationTrack();
    void InitializeCustomTrack();
    void ComputeActivationTrack(float time);
    void ComputeCustomTrack(float time);
    void ClearTimeline();
    std::vector<TimelineActivationClip*> waittingActiovationClip;
    std::vector<TimelineActivationClip*> runningActiovationClip;
    std::vector<TimelineCustomClip*> waittingCustomClip;
    std::vector<TimelineCustomClip*> runningCustomClip;
};

