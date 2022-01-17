#pragma once
class PostProcess
{
public:
	static void CreateInstance();
	static PostProcess* GetInstance();
	static void DestroyInstance();
	
	PostProcess();
	~PostProcess();
private:
	
protected:
	static PostProcess* instance;
};

