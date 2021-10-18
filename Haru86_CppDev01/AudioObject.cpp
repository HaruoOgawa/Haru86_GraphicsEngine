#include "AudioObject.h"
#include "./AudioSourceComponent.h"

AudioObject::AudioObject() 
	: Object()
{
	audioSource = new AudioSourceComponent(this);
	AddComponent(audioSource);
}

AudioObject::~AudioObject() {

}

bool AudioObject::Initialize() {
	return true;
}

void AudioObject::PlayAudio() {

}