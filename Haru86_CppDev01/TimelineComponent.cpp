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
		if (iter!= game->GetInstance()->gameObjectList.end()) {
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
	for (auto clip : waittingActiovationClip) {
		if (clip->startTime<time&&clip->endTime>=time) {
			game->GetInstance()->gameObjectList.emplace_back(clip->gameObject);
			runningActiovationClip.emplace_back(clip);
		}
	}

	for (auto clip : runningActiovationClip) {
		if (time>clip->endTime) {
			auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
			if (*(iter)) {
				game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
					+ std::distance(game->GetInstance()->gameObjectList.begin(), iter));
			}

			auto runningIter = std::find(runningActiovationClip.begin(), runningActiovationClip.end(), clip);
			if (*(runningIter)) {
				runningActiovationClip.erase(runningActiovationClip.begin()
					+ std::distance(runningActiovationClip.begin(), runningIter)
				);
			}

			waittingActiovationClip.emplace_back(clip);

		}
	}
}
void TimelineComponent::ComputeAnimationTrack(float time) {

}

void TimelineComponent::ClearTimeline() {
	for (auto clip : waittingActiovationClip) {
		delete clip->gameObject;
		delete clip;
	}
	waittingActiovationClip.clear();
	
	for (auto clip : runningActiovationClip) {
		delete clip->gameObject;
		delete clip;
	}
	runningActiovationClip.clear();

	for (auto clip : endActiovationClip) {
		delete clip->gameObject;
		delete clip;
	}
	endActiovationClip.clear();
}