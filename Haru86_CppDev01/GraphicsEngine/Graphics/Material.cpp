#include "Material.h"
#include <fstream>
#include <sstream>
#include "./SDL.h"
#include <iostream>
#include "GraphicsEngine/Graphics/ComputeBuffer.h"

Material::Material() {
	LoadShader("./Shader/Standard.vert", "./Shader/Standard.frag");
}

Material::Material(std::string vertexShaderName, std::string fragmentShaderName)
{
	LoadShader(vertexShaderName, fragmentShaderName);
}

Material::~Material() {
	UnLoadData();
}

void Material::LoadShader(std::string vertName, std::string fragName) {
	if (CompileShader(vertName,GL_VERTEX_SHADER,vertShaderData)&&
		CompileShader(fragName,GL_FRAGMENT_SHADER,fragShaderData)) {
		
		shaderPrg = glCreateProgram();
		glAttachShader(shaderPrg, vertShaderData);
		glAttachShader(shaderPrg, fragShaderData);
		glLinkProgram(shaderPrg);

		GLint status;
		glGetProgramiv(shaderPrg, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			SDL_Log("Cannot Load Program Data");
			char buffer[512];
			memset(buffer, 0, 512);
			glGetProgramInfoLog(shaderPrg, 511, nullptr, buffer);
			SDL_Log("GLSL Link Status:\n%s", buffer);
		}
		else
		{
			//SDL_Log("Success!! Loaded All Shader file");
		}
	}
}

bool Material::CompileShader(std::string shadername, GLenum shaderType, GLuint& outShader) {
	
	std::ifstream shaderFile(shadername);
	if (shaderFile.is_open()) {
		
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);
	}
	else {
		SDL_Log("Failure!! cannot open shader file...");
	}

	GLint status;
	glGetShaderiv(outShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		SDL_Log("Cannnot Load Shader: %s",shadername.c_str());
		
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(outShader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed: %s", buffer);
		return false;
	}

	return true;
}

void Material::SetActive() {
	glUseProgram(shaderPrg);
}

void Material::SetMatrixUniform(std::string uniformName, glm::mat4 matrix) {
	GLuint location = glGetUniformLocation(shaderPrg, uniformName.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(&matrix[0][0]));
}

void Material::SetFloatUniform(std::string uniformName, float val) {
	GLuint location = glGetUniformLocation(shaderPrg, uniformName.c_str());
	glUniform1f(location, val);
}

void Material::SetVec2Uniform(std::string uniformName, glm::vec2 val) {
	GLuint location = glGetUniformLocation(shaderPrg, uniformName.c_str());
	glUniform2fv(location,1, reinterpret_cast<GLfloat*>(&val));
}

void Material::SetTexUniform(std::string uniformName, unsigned int val) {
	GLuint location = glGetUniformLocation(shaderPrg, uniformName.c_str());
	glUniform1i(location, static_cast<GLuint>(val-1));
}

void Material::SetBuffer(ComputeBuffer* buffer,int bufferIndex) {
	SetActive();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bufferIndex, buffer->ssbo);
}

void Material::UnLoadData() {
	glDeleteProgram(shaderPrg);
	glDeleteShader(vertShaderData);
	glDeleteShader(fragShaderData);
}