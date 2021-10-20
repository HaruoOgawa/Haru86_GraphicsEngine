#include "Material.h"
#include <fstream>
#include <sstream>
#include "./SDL.h"
#include <iostream>

Material::Material() {
	//std::cout << "Create Material" << std::endl;
	LoadShader("Standard.vert", "Standard.frag");
}

Material::Material(std::string vertexShaderName, std::string fragmentShaderName)
{
	//std::cout << "Create Material" << std::endl;
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
	//SDL_Log(shadername.c_str());

	std::ifstream shaderFile(shadername);
	if (shaderFile.is_open()) {
		//SDL_Log("Success!! opened shader file.");
		
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

void Material::UnLoadData() {
	glDeleteProgram(shaderPrg);
	glDeleteShader(vertShaderData);
	glDeleteShader(fragShaderData);
}