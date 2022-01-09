#include "CBoxInstancing.h"

CBoxInstancing::CBoxInstancing(Object* o)
	: Component(o, static_cast<std::string>(typeid(CBoxInstancing).name()).substr(6))
{
	printf("Attach CBoxInstancing\n");
}

CBoxInstancing::~CBoxInstancing() {
	printf("delete CBoxInstancing\n");
}

void CBoxInstancing::Start() {

}

void CBoxInstancing::Update() {

}

void CBoxInstancing::ProcessInput(const Uint8* state)const {

}