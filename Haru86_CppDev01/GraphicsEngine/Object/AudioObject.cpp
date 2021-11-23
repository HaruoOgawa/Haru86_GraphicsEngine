#include "../Object/AudioObject.h"
#include "../Component/AudioSourceComponent.h"
#include <iostream>

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