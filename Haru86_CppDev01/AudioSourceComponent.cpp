#include "AudioSourceComponent.h"
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <vector>

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

	mSystem->getLowLevelSystem(&lowLevelSystem);

	LoadBank("Assets/Master Bank.strings.bank");
	LoadBank("Assets/Master Bank.bank");

	return true;
}

void AudioSourceComponent::LoadBank(std::string fileName) {
	if (banksMap.find(fileName) != banksMap.end()) {
		return;
	}

	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = mSystem->loadBankFile(
		fileName.c_str(),
		FMOD_STUDIO_LOAD_BANK_NORMAL,
		&bank
	);

	const int maxPathLength = 512;

	if (result==FMOD_OK) {
		banksMap.emplace(fileName, bank);
		bank->loadSampleData();
		int numEvents = 0;
		bank->getEventCount(&numEvents);
		if (numEvents > 0) {
			std::vector<FMOD::Studio::EventDescription*> events(numEvents);
			bank->getEventList(events.data(), numEvents, &numEvents);

			char eventName[maxPathLength];
			for (int i = 0; i < numEvents; i++) {
				FMOD::Studio::EventDescription* e = events[i];
				e->getPath(eventName, maxPathLength, nullptr);
				eventMap.emplace(eventName, e);
			}

		}
	}

}
void AudioSourceComponent::UnLoadBask(std::string fileName) {
	auto item = banksMap.find(fileName);
	if (item == banksMap.end()) {
		return;
	}

	FMOD::Studio::Bank* bank = item->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0) {
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		bank->getEventList(events.data(), numEvents, &numEvents);
		char eventName[512];
		for (int i = 0; i < numEvents; i++) {
			FMOD::Studio::EventDescription* e = events[i];
			e->getPath(eventName, 512, nullptr);
			auto eventi = eventMap.find(eventName);
			if (eventi != eventMap.end()) {
				eventMap.erase(eventi);
			}
		}
	}

	bank->unloadSampleData();
	bank->unload();
	banksMap.erase(item);
}

void AudioSourceComponent::UnLoadAllBank() {
	for (auto& item : banksMap) {
		item.second->unloadSampleData();
		item.second->unload();
	}
	banksMap.clear();
	eventMap.clear();
}

void AudioSourceComponent::Update() {

}

void AudioSourceComponent::Shutdown() {
	
	UnLoadAllBank();

	if (mSystem) {
		mSystem->release();
	}
}