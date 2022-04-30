#include "Main.h"
#include <iostream>
#include "../../GraphicsMain/GraphicsMain.h"

int main(int argc, char** argv) {
	GraphicsMain::Create();
	
	if (GraphicsMain::GetInstance()->Initialize()) {
		GraphicsMain::GetInstance()->RunLoop();
	}

	//printf("GraphicsMain is Finished\n");

	GraphicsMain::GetInstance()->ShutDown();
	GraphicsMain::Destroy();

	//printf("GraphicsMain is Destroyed\n");

	return 0;
}