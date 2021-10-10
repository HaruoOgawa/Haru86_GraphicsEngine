#pragma once



class Game
{
public:
	Game();
	~Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();
private :
	bool isRunning = false;
};

