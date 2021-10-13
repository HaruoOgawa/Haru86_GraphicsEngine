#include "Material.h"
#include <fstream>
#include <sstream>
#include "./SDL.h"


Material::Material(std::string vertexShaderName, std::string fragmentShaderName)
{
	LoadShader(vertexShaderName, fragmentShaderName);
}

Material::~Material() {
	UnLoadData();
}

void Material::LoadShader(std::string vertName, std::string fragName) {
	if (CompileShader(vertName,GL_VERTEX_SHADER,vertShaderData)||
		CompileShader(fragName,GL_FRAGMENT_SHADER,fragShaderData)) {
		shaderPrg = glCreateProgram();
		glAttachShader(shaderPrg, vertShaderData);
		glAttachShader(shaderPrg, fragShaderData);
		glLinkProgram(shaderPrg);

		GLint status;
		glGetProgramiv(shaderPrg, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			SDL_Log("Cannot Load Program Data");
		}
	}
}

bool Material::CompileShader(std::string shadername, GLenum shaderType, GLuint& outShader) {
	std::ifstream shaderStream(shadername);
	if (shaderStream.is_open()) {
		std::stringstream sstream;
		sstream << shaderStream.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &(contentsChar), nullptr);

	}

	GLint status;
	glGetShaderiv(outShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		SDL_Log("Cannnot Load Shader");
		return false;
	}

	return true;
}

void Material::SetActive() {
	glUseProgram(shaderPrg);
}

void Material::SetMatrixUniform(std::string uniformName, glm::mat4 matrix) {
	GLuint location = glGetUniformLocation(shaderPrg, uniformName.c_str());
	//glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void Material::UnLoadData() {
	glDeleteProgram(shaderPrg);
	glDeleteShader(vertShaderData);
	glDeleteShader(fragShaderData);
}