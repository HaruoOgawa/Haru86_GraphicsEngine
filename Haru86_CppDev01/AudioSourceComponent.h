#pragma once
#include "Component.h"
#include "./Object.h"
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
private :
    FMOD::Studio::System* mSystem;
    FMOD::System* lowLevelSystem;
    void Shutdown();
};

