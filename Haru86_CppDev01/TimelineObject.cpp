#include "TimelineObject.h"
#include "./TimelineComponent.h"

TimelineObject::TimelineObject() {
	timelineComponent = new TimelineComponent(this);
	AddComponent(timelineComponent);
}
TimelineObject::~TimelineObject() {

}

void TimelineObject::AddActivationClip(GameObject* obj, float startTime, float endTime) {
	timelineComponent->waittingActiovationClip.emplace_back(new TimelineActivationClip(obj, startTime*1000.0f, endTime*1000.0f));
}

void TimelineObject::AddAnimationClip(class GameObject* obj, float startTime, float endTime) {

}

void TimelineObject::Initialize() {
	timelineComponent->Initialize();
}