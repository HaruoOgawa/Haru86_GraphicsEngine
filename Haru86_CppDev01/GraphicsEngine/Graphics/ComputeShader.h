#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

enum CorrectionType {
	COMPUTEBUFFER,
	ARRAY
};

class ComputeShader
{
public:
	ComputeShader(std::string shaderPath);
	~ComputeShader();
	void SetBuffer(class ComputeBuffer* buffer,class Material* material);
	void SetMatrixUniform(std::string uniformName, glm::mat4 matrix);
	void SetFloatUniform(std::string uniformName, float val);
	void SetVec2Uniform(std::string uniformName, glm::vec2 val);
	void SetTexUniform(std::string uniformName, unsigned int val);
	void Dispatch(int xGroupNum, int yGroupNum, int zGroupNum);
	void LoadComputeShader(std::string computeShaderPath);
	bool CompileShader(std::string shadername, GLuint& outShader);
	void BindComputeBuffer(CorrectionType correctionType);
	void DisBindComputeBuffer(CorrectionType correctionType);
	void SetActive();
private:
	GLuint shaderPrg;
	GLuint computeShaderData;
	//OpenGL‚Ì§–ñ‚É‚æ‚èˆê‚Â‚ÌComputeShader‚Ég‚¦‚éComputeBuffer‚Ì”‚ÍÅ‘å4ŒÂ‚Ü‚Å(index‚Ì”ÍˆÍ‚Í0`3)
	std::vector<ComputeBuffer*> m_buffers;
};

