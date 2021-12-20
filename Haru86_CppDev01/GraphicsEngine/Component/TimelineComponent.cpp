#include "TimelineComponent.h"
#include "../Object/Object.h"
#include "../Game/Game.h"
#include "../Object/GameObject.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "./MeshRendererComponent.h"

TimelineComponent::TimelineComponent(Object* o)
	:Component(o, static_cast<std::string>(typeid(TimelineComponent).name()).substr(6))
{
	timeVal = game->time;
	animTime = 0.0f;
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
	InitializeAnimationTrack();
}

void TimelineComponent::InitializeActivationTrack() {
	for (auto i = 0; i < waittingActiovationClip.size();i++) {
		auto clip = waittingActiovationClip[i];
		auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
		if (iter!= game->GetInstance()->gameObjectList.end()) {
			game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
				+std::distance(game->GetInstance()->gameObjectList.begin(), iter));
		}
	}
}
void TimelineComponent::InitializeCustomTrack() {
	for (auto i = 0; i < waittingCustomClip.size(); i++) {
		auto clip = waittingCustomClip[i];
		auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
		if (iter != game->GetInstance()->gameObjectList.end()) {
			game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
				+ std::distance(game->GetInstance()->gameObjectList.begin(), iter));
		}
	}
}

void TimelineComponent::InitializeAnimationTrack() {
	
}

void TimelineComponent::ComputeTimeline(float time) {
	ComputeActivationTrack(time);
	ComputeCustomTrack(time);
	ComputeAnimationTrack(time);
}

void TimelineComponent::ComputeActivationTrack(float time) {
	for (auto i = 0; i < waittingActiovationClip.size(); i++) {
		auto clip = waittingActiovationClip[i];
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

	for (auto i = 0; i < runningActiovationClip.size(); i++) {
		auto clip = runningActiovationClip[i];
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
	for (auto i = 0; i < waittingCustomClip.size(); i++) {
		auto clip = waittingCustomClip[i];
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

	for (auto i = 0; i < runningCustomClip.size(); i++) {
		auto clip = runningCustomClip[i];
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

void TimelineComponent::ComputeAnimationTrack(float time) {
	for (auto i = 0; i < waittingAnimationClip.size(); i++) {
		auto clip = waittingAnimationClip[i];
		if (clip->startTime < time && clip->endTime >= time) {
			clip->lifeTime = 0.0f;
			clip->lifeTimeRate = 0.0f;
			clip->gameObject->meshComp->animationClips.emplace_back(clip);
			runningAnimationClip.emplace_back(clip);

			auto waittingIter = std::find(waittingAnimationClip.begin(), waittingAnimationClip.end(), clip);
			if (waittingIter != waittingAnimationClip.end()) {
				waittingAnimationClip.erase(waittingAnimationClip.begin()
					+ std::distance(waittingAnimationClip.begin(), waittingIter)
				);
			}
		}
	}

	for (auto i = 0; i < runningAnimationClip.size(); i++) {
		auto clip = runningAnimationClip[i];
		clip->lifeTime += Game::GetInstance()->deltaTime;
		clip->lifeTimeRate = clip->lifeTime / (clip->endTime*0.001f - clip->startTime * 0.001f);
		if (time > clip->endTime) {
			auto iter = std::find(clip->gameObject->meshComp->animationClips.begin(), clip->gameObject->meshComp->animationClips.end(), clip);
			if (iter!= clip->gameObject->meshComp->animationClips.end()) {
				clip->gameObject->meshComp->animationClips.erase(clip->gameObject->meshComp->animationClips.begin()
					+ std::distance(clip->gameObject->meshComp->animationClips.begin(), iter));
			}

			auto runningIter = std::find(runningAnimationClip.begin(), runningAnimationClip.end(), clip);
			if (runningIter!= runningAnimationClip.end()) {
				runningAnimationClip.erase(runningAnimationClip.begin()
					+ std::distance(runningAnimationClip.begin(), runningIter)
				);
			}

			waittingAnimationClip.emplace_back(clip);

		}
	}
}

void TimelineComponent::ResetTimeline() {
	for (auto i = 0; i < runningActiovationClip.size(); i++) {
		auto clip = runningActiovationClip[i];
		auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
		if (iter != game->GetInstance()->gameObjectList.end()) {
			game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
				+ std::distance(game->GetInstance()->gameObjectList.begin(), iter));
		}

		waittingActiovationClip.emplace_back(clip);
	}
	runningActiovationClip.clear();
	
	for (auto i = 0; i < runningCustomClip.size(); i++) {
		auto clip = runningCustomClip[i];
		auto iter = std::find(game->GetInstance()->gameObjectList.begin(), game->GetInstance()->gameObjectList.end(), clip->gameObject);
		if (iter != game->GetInstance()->gameObjectList.end()) {
			game->GetInstance()->gameObjectList.erase(game->GetInstance()->gameObjectList.begin()
				+ std::distance(game->GetInstance()->gameObjectList.begin(), iter));
		}

		waittingCustomClip.emplace_back(clip);
	}
	runningCustomClip.clear();
	
	for (auto i = 0; i < runningAnimationClip.size(); i++) {
		auto clip = runningAnimationClip[i];
		clip->lifeTime = 0.0f;
		clip->lifeTimeRate = 0.0f;
		clip->gameObject->meshComp->animationClips.clear();
		waittingAnimationClip.emplace_back(clip);
	}
	runningAnimationClip.clear();

}

void TimelineComponent::ClearTimeline() {
	//activation//////////////////
	waittingActiovationClip.clear();
	runningActiovationClip.clear();
	//Custom Activation////////////////
	waittingCustomClip.clear();
	runningCustomClip.clear();
	//Animation////////////////
	waittingAnimationClip.clear();
	runningAnimationClip.clear();

}

void TimelineComponent::ProcessInput(const Uint8* state)const {

}