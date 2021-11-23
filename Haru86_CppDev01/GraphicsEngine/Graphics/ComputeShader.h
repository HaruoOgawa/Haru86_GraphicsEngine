#pragma once
#include <string>

class ComputeShader
{
public:
	ComputeShader();
	~ComputeShader();
	void SetBuffer();
	void SetFloat();
	void SetMatrix4x4();
	std::string computeShaderPath;
};

