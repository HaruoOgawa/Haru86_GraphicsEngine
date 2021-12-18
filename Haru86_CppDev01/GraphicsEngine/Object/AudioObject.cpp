#include "../Object/AudioObject.h"
#include "../Component/AudioSourceComponent.h"
#include <iostream>

AudioObject::AudioObject() 
	: Object()
{
	audioSource =  std::make_shared<AudioSourceComponent>(this);
	AddComponent(audioSource);
}

AudioObject::AudioObject(std::string audioSourcePath)
	: Object()
{
	audioSource = std::make_shared<AudioSourceComponent>(this, audioSourcePath);
	AddComponent(audioSource);
}

AudioObject::~AudioObject() {

}

bool AudioObject::Initialize() {
	if (!audioSource->Initialize()) {
		return false;
	}

	return true;
}

void AudioObject::PlayAudio() {
	audioSource->Play();
}