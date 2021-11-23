#pragma once
#include "Component.h"
#include "../Object/Object.h"
#include <string>
#include <unordered_map>

namespace FMOD
{
	class System;
	class Channel;
	class Event;
	namespace Studio
	{
		class Bank;
		class EventDescription;
		class EventInstance;
		class System;
		class Bus;
	};
};


class AudioSourceComponent :
    public Component
{
public:
    AudioSourceComponent(class Object* o);
    AudioSourceComponent(class Object* o, std::string audioSourcePath);
    ~AudioSourceComponent();
    bool Initialize();
	void Update() override;
	void ProcessInput(const Uint8* state)const override;
	int GetAudioLength();
	void SkipAudio(float startTime);
	bool StopAudioCheck(float startTime);
private :
    void Shutdown();
	void LoadBank(std::string fileName);
	void UnLoadBask(std::string fileName);
	void UnLoadAllBank();
	void CreateSound(std::string name);
	void UnLoadSound();
	FMOD::Studio::System* mSystem;
	FMOD::System* lowLevelSystem;
	std::unordered_map<std::string, FMOD::Studio::Bank*> banksMap;
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> eventMap;
	FMOD::Channel* channel;
	std::string m_audioSourcePath;
};

