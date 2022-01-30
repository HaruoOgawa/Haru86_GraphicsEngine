#include "GraphicsEngine/Object/Object.h"
#include "CKura3DGPUTrail.h"

CKura3DGPUTrail::CKura3DGPUTrail(Object* o)
	: Component(o, static_cast<std::string>(typeid(CKura3DGPUTrail).name()).substr(6))
{

}

CKura3DGPUTrail::~CKura3DGPUTrail() {
}

void CKura3DGPUTrail::Start() {

}

void CKura3DGPUTrail::Update() {

}

void CKura3DGPUTrail::Draw() {

}

void CKura3DGPUTrail::ProcessInput(const Uint8* state)const {

}