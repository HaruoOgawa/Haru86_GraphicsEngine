#include "../Object/AudioObject.h"
#include "../Component/AudioSourceComponent.h"
#include <iostream>

AudioObject::AudioObject() 
	: Object()
{
	

	audioSource = new AudioSourceComponent(this);
	AddComponent(audioSource);
}

AudioObject::AudioObject(std::string audioSourcePath)
	: Object()
{
	audioSource = new AudioSourceComponent(this, audioSourcePath);
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