#include "AudioSourceComponent.h"
#include <fmod_studio.hpp>
#include <fmod_errors.h>

AudioSourceComponent::AudioSourceComponent(class Object* o)
	: Component(o)
{

}

AudioSourceComponent::~AudioSourceComponent() {

}

bool AudioSourceComponent::Initialize() {
	FMOD::Debug_Initialize(
		FMOD_DEBUG_LEVEL_ERROR,
		FMOD_DEBUG_MODE_TTY
	);

	FMOD_RESULT result;
	result = FMOD::Studio::System::create(&mSystem);
	if (result != FMOD_OK) {
		SDL_Log("FMOD‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½: %s",FMOD_ErrorString(result));
		return false;
	}
	
	result = mSystem->initialize(
		512,
		FMOD_STUDIO_INIT_NORMAL,
		FMOD_INIT_NORMAL,
		nullptr
	);

	if (result!=FMOD_OK) {
		SDL_Log("FMOD‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½: %s", FMOD_ErrorString(result));
		return false;
	}

	//mSystem->getLowLevelSystem(&lowLevelSystem);
	mSystem->getLowLevelSystem(&lowLevelSystem);

	return true;
}

void AudioSourceComponent::Shutdown() {
	if (mSystem) {
		mSystem->release();
	}
}