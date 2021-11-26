#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <memory>

class ComputeShader
{
public:
	ComputeShader(std::string shaderPath);
	~ComputeShader();
	void SetBuffer(class ComputeBuffer* buffer);
	void SetFloat();
	void SetMatrix4x4();
	void Dispatch(int xGroupNum, int yGroupNum, int zGroupNum);
	void LoadComputeShader(std::string computeShaderPath);
	bool CompileShader(std::string shadername, GLuint& outShader);
	std::string computeShaderPath;
private:
	GLuint shaderPrg;
	GLuint computeShaderData;
	//OpenGL‚Ì§–ñ‚É‚æ‚èˆê‚Â‚ÌComputeShader‚Ég‚¦‚éComputeBuffer‚Ì”‚ÍÅ‘å4ŒÂ‚Ü‚Å(index‚Ì”ÍˆÍ‚Í0`3)
	std::vector<ComputeBuffer*> m_buffers;
};

