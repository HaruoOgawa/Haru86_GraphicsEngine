#include "TimelineObject.h"
#include "../Component/TimelineComponent.h"

TimelineObject::TimelineObject() {
	timelineComponent =  std::make_shared<TimelineComponent>(this);
	AddComponent(timelineComponent);
}
TimelineObject::~TimelineObject() {

}

void TimelineObject::AddActivationClip(std::shared_ptr<GameObject> obj, float startTime, float endTime) {
	if (endTime < startTime) {
		return;
	}
	else {
		timelineComponent->waittingActiovationClip.emplace_back(std::make_shared<TimelineActivationClip>(obj, startTime * 1000.0f, endTime * 1000.0f));
	}
}

void TimelineObject::AddCustomClip(std::shared_ptr<GameObject> obj, float startTime, float endTime, std::function<void(void)> callback) {
	timelineComponent->waittingCustomClip.emplace_back(std::make_shared<TimelineCustomClip>(obj,startTime*1000.0f,endTime*1000.0f,callback));
	
}

void TimelineObject::AddAnimationClip(std::shared_ptr<GameObject> obj, float startTime, float endTime, std::function<void(float)> callback) {
	timelineComponent->waittingAnimationClip.emplace_back(std::make_shared<TimelineAnimationClip>(obj,startTime*1000.0f,endTime*1000.0f,callback));
	
}

void TimelineObject::Initialize() {
	timelineComponent->Initialize();
}