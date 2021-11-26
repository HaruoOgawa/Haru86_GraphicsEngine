#include "ComputeShader.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL.h>
#include <fstream>
#include <sstream>
#include "GraphicsEngine/Graphics/ComputeBuffer.h"

ComputeShader::ComputeShader(std::string shaderPath) {
	LoadComputeShader(shaderPath);
}

ComputeShader::~ComputeShader() {

}

void ComputeShader::SetBuffer(ComputeBuffer* buffer) {
	if (m_buffers.size() < 4) {
		//ここでBufferをセットする。スマートポインタの所有権を譲渡する必要がありそう

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

	for (int i = 0; i < m_buffers.size();i++) {
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER,i ,m_buffers[i]->ssbo);
	}

	glDispatchCompute(xGroupNum, yGroupNum, zGroupNum);

	for (int i = 0; i < m_buffers.size(); i++) {
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER,i ,0 );
	}
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