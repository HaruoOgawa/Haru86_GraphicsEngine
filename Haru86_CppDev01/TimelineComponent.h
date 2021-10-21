#pragma once
#include "Component.h"
#include <vector>

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
    void InitializeAnimationTrack();
    void ComputeActivationTrack(float time);
    void ComputeAnimationTrack(float time);
    void ClearTimeline();
    std::vector<TimelineActivationClip*> waittingActiovationClip;
    std::vector<TimelineActivationClip*> runningActiovationClip;
    std::vector<TimelineActivationClip*> endActiovationClip;
};

