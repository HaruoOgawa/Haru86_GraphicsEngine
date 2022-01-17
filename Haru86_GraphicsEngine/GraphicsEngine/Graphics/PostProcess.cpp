#include "PostProcess.h"
#include <iostream>

//instance‚ð’è‹`‚·‚é
PostProcess* PostProcess::instance = nullptr;

void PostProcess::CreateInstance() {
	if (!instance)instance = new PostProcess();
}

PostProcess* PostProcess::GetInstance() {
	if (instance) return instance;
}

void PostProcess::DestroyInstance() {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

PostProcess::PostProcess() {
	printf("Create PostProcess Instance\n");
}

PostProcess::~PostProcess() {

}
