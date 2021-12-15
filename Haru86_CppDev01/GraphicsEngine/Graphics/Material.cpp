#include "Material.h"
#include <fstream>
#include <sstream>
#include "./SDL.h"
#include <iostream>
#include "GraphicsEngine/Graphics/ComputeBuffer.h"
#include "GraphicsEngine/Graphics/Texture.h"

Material::Material() {
	LoadShader("./Assets/Shader/Standard.vert", "./Assets/Shader/Standard.frag");
}

Material::Material(std::map<GLenum, std::string> shaders) {
	LoadShader(shaders);
}

Material::Material(std::string vertexShaderName, std::string fragmentShaderName)
{
	LoadShader(vertexShaderName, fragmentShaderName);
}

Material::Material(std::string vertexShaderName, std::string tessellationShaderName[2], std::string fragmentShaderName)
{
	LoadShader(vertexShaderName,tessellationShaderName, fragmentShaderName);
}

Material::Material(std::string vertexShaderName, std::string geometryShaderName, std::string fragmentShaderName)
{
	LoadShader(vertexShaderName, geometryShaderName, fragmentShaderName);
}

Material::~Material() {
	UnLoadData();
}

void Material::LoadShader(std::map<GLenum, std::string> shaders) {
	bool compileResult = false;

	for (auto shader : shaders) {
		switch (shader.first)
		{
		case GL_VERTEX_SHADER:
			compileResult = CompileShader(shader.second, shader.first, vertShaderData);
			break;
		case GL_TESS_CONTROL_SHADER:
			compileResult = CompileShader(shader.second, shader.first, tessControlShaderData);
			break;
		case GL_TESS_EVALUATION_SHADER:
			compileResult = CompileShader(shader.second, shader.first, tessEvalShaderData);
			break;
		case GL_GEOMETRY_SHADER:
			compileResult = CompileShader(shader.second, shader.first, geometryShaderData);
			break;
		case GL_FRAGMENT_SHADER:
			compileResult = CompileShader(shader.second, shader.first, fragShaderData);
			break;
		default:
			compileResult = false;
			break;
		}

		if (!compileResult) {
			printf("Compile is failure...\n");
			break;
		}
		
	}
	
	if (compileResult) {
		
		shaderPrg = glCreateProgram();
		
		for (auto shader : shaders) {
			switch (shader.first)
			{
			case GL_VERTEX_SHADER:
				glAttachShader(shaderPrg, vertShaderData);
				break;
			case GL_TESS_CONTROL_SHADER:
				glAttachShader(shaderPrg, tessControlShaderData);
				break;
			case GL_TESS_EVALUATION_SHADER:
				glAttachShader(shaderPrg, tessEvalShaderData);
				break;
			case GL_GEOMETRY_SHADER:
				glAttachShader(shaderPrg, geometryShaderData);
				break;
			case GL_FRAGMENT_SHADER:
				glAttachShader(shaderPrg, fragShaderData);
				break;
			default:
				break;
			}
		}

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
	}
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

void Material::LoadShader(std::string vertName, std::string tessellationShaderName[2], std::string fragName) {
	if (CompileShader(vertName,GL_VERTEX_SHADER,vertShaderData)&&
		CompileShader(tessellationShaderName[0], GL_TESS_CONTROL_SHADER,tessControlShaderData)&&
		CompileShader(tessellationShaderName[1],GL_TESS_EVALUATION_SHADER,tessEvalShaderData)&&
		CompileShader(fragName,GL_FRAGMENT_SHADER,fragShaderData)) {
		
		shaderPrg = glCreateProgram();
		glAttachShader(shaderPrg, vertShaderData);
		glAttachShader(shaderPrg, tessControlShaderData);
		glAttachShader(shaderPrg, tessEvalShaderData);
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

void Material::LoadShader(std::string vertName, std::string geomName, std::string fragName) {
	if (CompileShader(vertName,GL_VERTEX_SHADER,vertShaderData)&&
		CompileShader(geomName,GL_GEOMETRY_SHADER, geometryShaderData)&&
		CompileShader(fragName,GL_FRAGMENT_SHADER,fragShaderData)) {
		
		shaderPrg = glCreateProgram();
		glAttachShader(shaderPrg, vertShaderData);
		glAttachShader(shaderPrg, geometryShaderData);
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

void Material::SetIntUniform(std::string uniformName, int val) {
	GLuint location = glGetUniformLocation(shaderPrg, uniformName.c_str());
	glUniform1i(location, val);
}

void Material::SetVec2Uniform(std::string uniformName, glm::vec2 val) {
	GLuint location = glGetUniformLocation(shaderPrg, uniformName.c_str());
	glUniform2fv(location,1, reinterpret_cast<GLfloat*>(&val));
}

void Material::SetVec3Uniform(std::string uniformName, glm::vec3 val) {
	GLuint location = glGetUniformLocation(shaderPrg, uniformName.c_str());
	glUniform3fv(location,1, reinterpret_cast<GLfloat*>(&val));
}

void Material::SetTexUniform(std::string uniformName, unsigned int val) {
	GLuint location = glGetUniformLocation(shaderPrg, uniformName.c_str());
	//glUniform1i(location, static_cast<GLuint>(val-1));
	glUniform1i(location, static_cast<GLuint>(val));
}

void Material::SetBuffer(std::shared_ptr<ComputeBuffer> buffer,int bufferIndex) {
	SetActive();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bufferIndex, buffer->ssbo);
}

void Material::LoadTextureList(std::vector<std::string> texPathList, std::vector<std::string> texUniformNameList) {
	for (int i = 0; i < texPathList.size();i++) {
		
		std::unique_ptr<Texture> tex = std::make_unique<Texture>();
		tex->texUniformName = texUniformNameList[i];
		if (!tex->Load(texPathList[i])) {
			printf("Cannot Load This Texture\n");
		}
		else {

			m_texture_list.push_back(std::move(tex));
		}
	}
}
void Material::SetActiveTextureList() {
	for (int i = 0; i < m_texture_list.size(); i++) {
		m_texture_list[i]->SetActive();
		SetTexUniform(m_texture_list[i]->texUniformName, m_texture_list[i]->GetTextureID());
	}
}

void Material::SetEactiveTextureList() {
	for (int i = 0; i < m_texture_list.size(); i++) {
		m_texture_list[i]->SetEactive();
	}
}


void Material::UnLoadData() {
	glDeleteProgram(shaderPrg);
	glDeleteShader(vertShaderData);
	glDeleteShader(fragShaderData);
}