#pragma once
#include "./Game.h"

#include "./VertexArray.h"

class App
{
public:
	App(class Game* g);
	~App();
	void Start();
	void Update();
private:
	class Game* game;
};

