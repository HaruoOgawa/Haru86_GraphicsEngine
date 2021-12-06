#include "KuraTrail.h"

KuraTrail::KuraTrail(Object* o) 
	: Component(o, static_cast<std::string>(typeid(KuraTrail).name()).substr(6))
{
	Start();
}

KuraTrail::~KuraTrail() {

}

void KuraTrail::Start() {
	printf("KuraTrail Start\n");
}

void KuraTrail::Update() {
	printf("KuraTrail Update\n");
}

void KuraTrail::ProcessInput(const Uint8* state)const {

}

void KuraTrail::Draw() {
	printf("KuraTrail Draw\n");
}