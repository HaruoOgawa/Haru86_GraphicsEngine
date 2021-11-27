#include "ComputeShader.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL.h>
#include <fstream>
#include <sstream>
#include "GraphicsEngine/Graphics/ComputeBuffer.h"
#include "GraphicsEngine/Graphics/Material.h"

ComputeShader::ComputeShader(std::string shaderPath) {
	LoadComputeShader(shaderPath);
}

ComputeShader::~ComputeShader() {
	m_buffers.clear();
}

void ComputeShader::SetBuffer(ComputeBuffer* buffer, Material* material) {
	if (m_buffers.size() < 4) {
		m_buffers.push_back(buffer);
		//‚»‚ê‚¼‚ê‚ÌShader‚ÉBuffer‚ðƒZƒbƒg
		material->SetBuffer(buffer, m_buffers.size() - 1);
		SetActive();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_buffers.size() - 1, buffer->ssbo);
		
	}
	else {
		return;
	}
}

void ComputeShader::SetFloat() {

}

void ComputeShader::SetMatrix4x4() {

}



void ComputeShader::Dispatch(int xGroupNum, int yGroupNum, int zGroupNum) {
	glUseProgram(shaderPrg);
	glDispatchCompute(xGroupNum, yGroupNum, zGroupNum);
}


void ComputeShader::LoadComputeShader(std::string computeShaderPath) {
	if (CompileShader(computeShaderPath, computeShaderData)) {

		shaderPrg = glCreateProgram();
		glAttachShader(shaderPrg, computeShaderData);
		glLinkProgram(shaderPrg);

		GLint status;
		glGetProgramiv(shaderPrg, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			SDL_Log("Cannot Load Program Data(ComputeShader)");
			char buffer[512];
			memset(buffer, 0, 512);
			glGetProgramInfoLog(shaderPrg, 511, nullptr, buffer);
			SDL_Log("GLSL Link Status(ComputeShader):\n%s", buffer);
		}
	}
}

bool ComputeShader::CompileShader(std::string shadername, GLuint& outShader) {

	std::ifstream shaderFile(shadername);
	if (shaderFile.is_open()) {

		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		outShader = glCreateShader(GL_COMPUTE_SHADER);
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);
	}
	else {
		SDL_Log("Failure!! cannot open shader file...");
	}

	GLint status;
	glGetShaderiv(outShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		SDL_Log("Cannnot Load Shader: %s", shadername.c_str());

		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(outShader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed: %s", buffer);
		return false;
	}

	return true;
}

void ComputeShader::BindComputeBuffer(CorrectionType correctionType) {
	if (correctionType == CorrectionType::COMPUTEBUFFER) {
		for (int i = 0; i < m_buffers.size(); i++) {
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, m_buffers[i]->ssbo);
		}
	}
	else if(correctionType == CorrectionType::ARRAY) {
		for (int i = 0; i < m_buffers.size(); i++) {
			glBindBuffer(GL_ARRAY_BUFFER, m_buffers[i]->ssbo);
		}
	}
	printf("m_buffers.size():%d \n",m_buffers.size());
}

void ComputeShader::DisBindComputeBuffer(CorrectionType correctionType) {
	if (correctionType == CorrectionType::COMPUTEBUFFER) {
		for (int i = 0; i < m_buffers.size(); i++) {
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i,0);
		}
	}
	else if(correctionType == CorrectionType::ARRAY) {
		for (int i = 0; i < m_buffers.size(); i++) {
			glBindBuffer(GL_ARRAY_BUFFER,0);
		}
	}
}

void ComputeShader::SetActive() {
	glUseProgram(shaderPrg);
}