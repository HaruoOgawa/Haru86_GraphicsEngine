#include "TimelineComponent.h"
#include "./Object.h"
#include "./Game.h"
#include <iostream>
#include <vector>

TimelineComponent::TimelineComponent(Object* o)
	:Component(o)
{
	timeVal = game->time;
}
TimelineComponent::~TimelineComponent() {
	ClearTimeline();
}

void TimelineComponent::Update() {
	timeVal = game->time;
	ComputeTimeline(timeVal);
}

void TimelineComponent::Initialize() {
	InitializeActivationTrack();
	InitializeAnimationTrack();
}

void TimelineComponent::InitializeActivationTrack() {
	printf("Hello Timeline Initializer \n");
	for (auto clip : waittingActiovationClip) {
		printf("Hello Timeline Initializer for \n");
		auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
		if (*(iter)) {
			game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
				+std::distance(game->GetInstance()->gameObjectList.begin(), iter));
		}
	}
}
void TimelineComponent::InitializeAnimationTrack() {

}

void TimelineComponent::ComputeTimeline(float time) {
	ComputeActivationTrack(time);
	ComputeAnimationTrack(time);
}

void TimelineComponent::ComputeActivationTrack(float time) {
	printf("Confirm timeVal in Activation Track : %d \n", static_cast<int>(time));
}
void TimelineComponent::ComputeAnimationTrack(float time) {

}

void TimelineComponent::ClearTimeline() {
	waittingActiovationClip.clear();
	runningActiovationClip.clear();
	endActiovationClip.clear();
}