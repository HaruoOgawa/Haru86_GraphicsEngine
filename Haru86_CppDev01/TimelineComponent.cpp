#include "TimelineComponent.h"
#include "./Object.h"
#include "./Game.h"
#include <iostream>

TimelineComponent::TimelineComponent(Object* o)
	:Component(o)
{
	timeVal = game->time;
	Initialize();
}
TimelineComponent::~TimelineComponent() {
	ClearTimeline();
}

void TimelineComponent::Update() {
	timeVal = game->time;
	ComputeTimeline();

	printf("time: %d \n",static_cast<int>(timeVal));

}

void TimelineComponent::Initialize() {
	InitializeActivationTrack();
	InitializeAnimationTrack();
}

void TimelineComponent::InitializeActivationTrack() {

}
void TimelineComponent::InitializeAnimationTrack() {

}

void TimelineComponent::ComputeTimeline() {
	ComputeActivationTrack();
	ComputeAnimationTrack();
}

void TimelineComponent::ComputeActivationTrack() {

}
void TimelineComponent::ComputeAnimationTrack() {

}

void TimelineComponent::ClearTimeline() {
	waittingActiovationClip.clear();
	runningActiovationClip.clear();
	endActiovationClip.clear();
}