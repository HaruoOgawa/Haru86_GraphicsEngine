#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>

class ComputeShader
{
public:
	ComputeShader(std::string shaderPath);
	~ComputeShader();
	void SetBuffer();
	void SetFloat();
	void SetMatrix4x4();
	void Dispatch(class ComputeBuffer buffer, int xGroupNum, int yGroupNum, int zGroupNum);
	void LoadComputeShader(std::string computeShaderPath);
	bool CompileShader(std::string shadername, GLuint& outShader);
	std::string computeShaderPath;
private:
	GLuint shaderPrg;
	GLuint computeShaderData;
};

