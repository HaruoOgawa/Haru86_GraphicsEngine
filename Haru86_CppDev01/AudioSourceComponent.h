#pragma once
#include "Component.h"
#include "./Object.h"
#include <string>
#include <unordered_map>

namespace FMOD
{
	class System;
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
    ~AudioSourceComponent();
    bool Initialize();
	void Update() override;
private :
    void Shutdown();
	void LoadBank(std::string fileName);
	void UnLoadBask(std::string fileName);
	void UnLoadAllBank();
	FMOD::Studio::System* mSystem;
	FMOD::System* lowLevelSystem;
	std::unordered_map<std::string, FMOD::Studio::Bank*> banksMap;
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> eventMap;
};

