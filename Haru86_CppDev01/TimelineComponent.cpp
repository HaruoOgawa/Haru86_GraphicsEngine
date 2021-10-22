#include "TimelineComponent.h"
#include "./Object.h"
#include "./Game.h"
#include "./GameObject.h"
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
	InitializeCustomTrack();
}

void TimelineComponent::InitializeActivationTrack() {
	for (auto clip : waittingActiovationClip) {
		auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
		if (iter!= game->GetInstance()->gameObjectList.end()) {
			game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
				+std::distance(game->GetInstance()->gameObjectList.begin(), iter));
		}
	}
}
void TimelineComponent::InitializeCustomTrack() {
	for (auto clip : waittingCustomClip) {
		auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
		if (iter != game->GetInstance()->gameObjectList.end()) {
			game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
				+ std::distance(game->GetInstance()->gameObjectList.begin(), iter));
		}
	}
}

void TimelineComponent::ComputeTimeline(float time) {
	ComputeActivationTrack(time);
	ComputeCustomTrack(time);
}

void TimelineComponent::ComputeActivationTrack(float time) {
	for (auto clip : waittingActiovationClip) {
		if (clip->startTime<time&&clip->endTime>=time) {
			game->GetInstance()->gameObjectList.emplace_back(clip->gameObject);
			runningActiovationClip.emplace_back(clip);

			auto waittingIter = std::find(waittingActiovationClip.begin(), waittingActiovationClip.end(), clip);
			if (waittingIter != waittingActiovationClip.end()) {
				waittingActiovationClip.erase(waittingActiovationClip.begin()
					+ std::distance(waittingActiovationClip.begin(), waittingIter)
				);
			}
		}
	}

	for (auto clip : runningActiovationClip) {
		if (time>clip->endTime) {
			auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
			if (iter != game->GetInstance()->gameObjectList.end()) {
				game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
					+ std::distance(game->GetInstance()->gameObjectList.begin(), iter));
			}

			auto runningIter = std::find(runningActiovationClip.begin(), runningActiovationClip.end(), clip);
			if (runningIter!= runningActiovationClip.end()) {
				runningActiovationClip.erase(runningActiovationClip.begin()
					+ std::distance(runningActiovationClip.begin(), runningIter)
				);
			}

			waittingActiovationClip.emplace_back(clip);

		}
	}
}
void TimelineComponent::ComputeCustomTrack(float time) {
	for (auto clip : waittingCustomClip) {
		if (clip->startTime < time && clip->endTime >= time) {
			clip->callback();
			game->GetInstance()->gameObjectList.emplace_back(clip->gameObject);
			runningCustomClip.emplace_back(clip);

			auto waittingIter = std::find(waittingCustomClip.begin(), waittingCustomClip.end(), clip);
			if (waittingIter != waittingCustomClip.end()) {
				waittingCustomClip.erase(waittingCustomClip.begin()
					+ std::distance(waittingCustomClip.begin(), waittingIter)
				);
			}
		}
	}

	for (auto clip : runningCustomClip) {
		if (time > clip->endTime) {
			auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
			if (iter!=game->GetInstance()->gameObjectList.end()) {
				game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
					+ std::distance(game->GetInstance()->gameObjectList.begin(), iter));
			}

			auto runningIter = std::find(runningCustomClip.begin(), runningCustomClip.end(), clip);
			if (runningIter!= runningCustomClip.end()) {
				runningCustomClip.erase(runningCustomClip.begin()
					+ std::distance(runningCustomClip.begin(), runningIter)
				);
			}

			waittingCustomClip.emplace_back(clip);

		}
	}
}

void TimelineComponent::ClearTimeline() {
	for (auto clip : waittingActiovationClip) {
		if (clip->gameObject != nullptr) {
			delete clip->gameObject;
		}
		
		if (clip != nullptr) {
			delete clip;
		}
	}
	waittingActiovationClip.clear();
	
	for (auto clip : runningActiovationClip) {
		if (clip->gameObject != nullptr) {
			delete clip->gameObject;
		}

		if (clip != nullptr) {
			delete clip;
		}
	}
	runningActiovationClip.clear();
	
	for (auto clip : waittingCustomClip) {
		if (clip->gameObject != nullptr) {
			delete clip->gameObject;
		}

		if (clip != nullptr) {
			delete clip;
		}
	}
	waittingCustomClip.clear();
	
	for (auto clip : runningCustomClip) {
		if (clip->gameObject != nullptr) {
			delete clip->gameObject;
		}

		if (clip != nullptr) {
			delete clip;
		}
	}
	runningCustomClip.clear();

}

void TimelineComponent::ProcessInput(const Uint8* state)const {

}