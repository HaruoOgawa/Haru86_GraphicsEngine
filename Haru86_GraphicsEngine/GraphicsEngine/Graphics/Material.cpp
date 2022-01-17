#include "Material.h"
#include <fstream>
#include <sstream>
#include "./SDL.h"
#include <iostream>
#include "GraphicsEngine/Graphics/ComputeBuffer.h"
#include "GraphicsEngine/Graphics/Texture.h"
#include "GraphicsEngine/Game/Game.h"

Material::Material() {
	LoadShader("./Assets/Shader/Standard.vert", "./Assets/Shader/Standard.frag", shaderPrg
		, vertShaderData, tessControlShaderData, tessEvalShaderData, geometryShaderData, fragShaderData);
	LoadShader("./Assets/Shader/Standard.vert", "./Assets/Shader/DepthColor.frag", depthShaderPrg
		, depthVertShaderData, depthTessControlShaderData, depthTessEvalShaderData, depthGeometryShaderData, depthFragShaderData);
}

Material::Material(std::map<GLenum, std::string> shaders) {
	LoadShader(shaders, shaderPrg
		, vertShaderData, tessControlShaderData, tessEvalShaderData, geometryShaderData, fragShaderData);
	auto depthShaders = shaders;
	depthShaders[GL_FRAGMENT_SHADER] = "./Assets/Shader/DepthColor.frag";
	LoadShader(depthShaders, depthShaderPrg
		, depthVertShaderData, depthTessControlShaderData, depthTessEvalShaderData, depthGeometryShaderData, depthFragShaderData);
}

Material::Material(std::string vertexShaderName, std::string fragmentShaderName)
{
	LoadShader(vertexShaderName, fragmentShaderName, shaderPrg
		, vertShaderData, tessControlShaderData, tessEvalShaderData, geometryShaderData, fragShaderData);
	LoadShader(vertexShaderName, "./Assets/Shader/DepthColor.frag", depthShaderPrg
		, depthVertShaderData, depthTessControlShaderData, depthTessEvalShaderData, depthGeometryShaderData, depthFragShaderData);
}

Material::Material(std::string vertexShaderName, std::string fragmentShaderName, RenderingSurfaceType renderingSurfaceType) {
	LoadShader(vertexShaderName, fragmentShaderName, shaderPrg
		, vertShaderData, tessControlShaderData, tessEvalShaderData, geometryShaderData, fragShaderData);
	if (renderingSurfaceType==RenderingSurfaceType::POLYGON) {
		LoadShader(vertexShaderName, "./Assets/Shader/DepthColor.frag", depthShaderPrg
			, depthVertShaderData, depthTessControlShaderData, depthTessEvalShaderData, depthGeometryShaderData, depthFragShaderData);
	}
}

Material::Material(std::string vertexShaderName, std::string tessellationShaderName[2], std::string fragmentShaderName)
{
	LoadShader(vertexShaderName,tessellationShaderName, fragmentShaderName, shaderPrg
		, vertShaderData, tessControlShaderData, tessEvalShaderData, geometryShaderData, fragShaderData);
	LoadShader(vertexShaderName,tessellationShaderName, "./Assets/Shader/DepthColor.frag", depthShaderPrg
		, depthVertShaderData, depthTessControlShaderData, depthTessEvalShaderData, depthGeometryShaderData, depthFragShaderData);
}

Material::Material(std::string vertexShaderName, std::string geometryShaderName, std::string fragmentShaderName)
{
	LoadShader(vertexShaderName, geometryShaderName, fragmentShaderName, shaderPrg
		, vertShaderData, tessControlShaderData, tessEvalShaderData, geometryShaderData, fragShaderData);
	LoadShader(vertexShaderName, geometryShaderName, "./Assets/Shader/DepthColor.frag", depthShaderPrg
		, depthVertShaderData, depthTessControlShaderData, depthTessEvalShaderData, depthGeometryShaderData, depthFragShaderData);
}

Material::~Material() {
	UnLoadData();
}

void Material::LoadShader(std::map<GLenum, std::string> shaders, GLuint& prg, GLuint& vert, GLuint& tc, GLuint& tv, GLuint& geom, GLuint& frag) {
	bool compileResult = false;

	for (auto shader : shaders) {
		switch (shader.first)
		{
		case GL_VERTEX_SHADER:
			compileResult = CompileShader(shader.second, shader.first, vert);
			break;
		case GL_TESS_CONTROL_SHADER:
			compileResult = CompileShader(shader.second, shader.first, tc);
			break;
		case GL_TESS_EVALUATION_SHADER:
			compileResult = CompileShader(shader.second, shader.first, tv);
			break;
		case GL_GEOMETRY_SHADER:
			compileResult = CompileShader(shader.second, shader.first, geom);
			break;
		case GL_FRAGMENT_SHADER:
			compileResult = CompileShader(shader.second, shader.first, frag);
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
		
		prg = glCreateProgram();
		
		for (auto shader : shaders) {
			switch (shader.first)
			{
			case GL_VERTEX_SHADER:
				glAttachShader(prg, vert);
				break;
			case GL_TESS_CONTROL_SHADER:
				glAttachShader(prg, tc);
				break;
			case GL_TESS_EVALUATION_SHADER:
				glAttachShader(prg, tv);
				break;
			case GL_GEOMETRY_SHADER:
				glAttachShader(prg, geom);
				break;
			case GL_FRAGMENT_SHADER:
				glAttachShader(prg, frag);
				break;
			default:
				break;
			}
		}

		glLinkProgram(prg);

		GLint status;
		glGetProgramiv(prg, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			SDL_Log("Cannot Load Program Data");
			char buffer[512];
			memset(buffer, 0, 512);
			glGetProgramInfoLog(prg, 511, nullptr, buffer);
			SDL_Log("GLSL Link Status:\n%s", buffer);
		}
	}
}
void Material::LoadShader(std::string vertName, std::string fragName, GLuint& prg, GLuint& vert, GLuint& tc, GLuint& tv, GLuint& geom, GLuint& frag) {
	if (CompileShader(vertName,GL_VERTEX_SHADER, vert)&&
		CompileShader(fragName,GL_FRAGMENT_SHADER,frag)) {
		
		prg = glCreateProgram();
		glAttachShader(prg, vert);
		glAttachShader(prg, frag);
		glLinkProgram(prg);

		GLint status;
		glGetProgramiv(prg, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			SDL_Log("Cannot Load Program Data");
			char buffer[512];
			memset(buffer, 0, 512);
			glGetProgramInfoLog(prg, 511, nullptr, buffer);
			SDL_Log("GLSL Link Status:\n%s", buffer);
		}
		else
		{
			//SDL_Log("Success!! Loaded All Shader file");
		}
	}
}

void Material::LoadShader(std::string vertName, std::string tessellationShaderName[2], std::string fragName, GLuint& prg, GLuint& vert, GLuint& tc, GLuint& tv, GLuint& geom, GLuint& frag) {
	if (CompileShader(vertName,GL_VERTEX_SHADER, vert)&&
		CompileShader(tessellationShaderName[0], GL_TESS_CONTROL_SHADER, tc)&&
		CompileShader(tessellationShaderName[1],GL_TESS_EVALUATION_SHADER, tv)&&
		CompileShader(fragName,GL_FRAGMENT_SHADER, frag)) {
		
		prg = glCreateProgram();
		glAttachShader(prg, vert);
		glAttachShader(prg, tc);
		glAttachShader(prg, tv);
		glAttachShader(prg, frag);
		glLinkProgram(prg);

		GLint status;
		glGetProgramiv(prg, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			SDL_Log("Cannot Load Program Data");
			char buffer[512];
			memset(buffer, 0, 512);
			glGetProgramInfoLog(prg, 511, nullptr, buffer);
			SDL_Log("GLSL Link Status:\n%s", buffer);
		}
		else
		{
			//SDL_Log("Success!! Loaded All Shader file");
		}
	}
}

void Material::LoadShader(std::string vertName, std::string geomName, std::string fragName, GLuint& prg, GLuint& vert, GLuint& tc, GLuint& tv, GLuint& geom, GLuint& frag) {
	if (CompileShader(vertName,GL_VERTEX_SHADER, vert)&&
		CompileShader(geomName,GL_GEOMETRY_SHADER, geom)&&
		CompileShader(fragName,GL_FRAGMENT_SHADER, frag)) {
		
		prg = glCreateProgram();
		glAttachShader(prg, vert);
		glAttachShader(prg, geom);
		glAttachShader(prg, frag);
		glLinkProgram(prg);

		GLint status;
		glGetProgramiv(prg, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) {
			SDL_Log("Cannot Load Program Data");
			char buffer[512];
			memset(buffer, 0, 512);
			glGetProgramInfoLog(prg, 511, nullptr, buffer);
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
	auto& prg = GetCurrentShaderPrg();
	glUseProgram(prg);
}

void Material::SetMatrixUniform(std::string uniformName, glm::mat4 matrix) {
	auto& prg = GetCurrentShaderPrg();
	GLuint location = glGetUniformLocation(prg, uniformName.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const float*>(&matrix[0][0]));
}

void Material::SetFloatUniform(std::string uniformName, float val) {
	auto& prg = GetCurrentShaderPrg();
	GLuint location = glGetUniformLocation(prg, uniformName.c_str());
	glUniform1f(location, val);
}

void Material::SetIntUniform(std::string uniformName, int val) {
	auto& prg = GetCurrentShaderPrg();
	GLuint location = glGetUniformLocation(prg, uniformName.c_str());
	glUniform1i(location, val);
}

void Material::SetVec2Uniform(std::string uniformName, glm::vec2 val) {
	auto& prg = GetCurrentShaderPrg();
	GLuint location = glGetUniformLocation(prg, uniformName.c_str());
	glUniform2fv(location,1, reinterpret_cast<GLfloat*>(&val));
}

void Material::SetVec3Uniform(std::string uniformName, glm::vec3 val) {
	auto& prg = GetCurrentShaderPrg();
	GLuint location = glGetUniformLocation(prg, uniformName.c_str());
	glUniform3fv(location,1, reinterpret_cast<GLfloat*>(&val));
}

void Material::SetTexUniform(std::string uniformName, unsigned int val) {
	auto& prg = GetCurrentShaderPrg();
	GLuint location = glGetUniformLocation(prg, uniformName.c_str());
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

GLuint& Material::GetCurrentShaderPrg() {
	if (depthShaderPrg) {
		printf("depthShaderPrg NOT null \n");
		if (Game::GetInstance()->renderingTarget == ERerderingTarget::COLOR) {
			return shaderPrg;
		}
		else if (Game::GetInstance()->renderingTarget == ERerderingTarget::DEPTH) {
			return depthShaderPrg;
		}
	}
	else {
		printf("depthShaderPrg is null... \n");
		return shaderPrg;
	}
}

void Material::UnLoadData() {
	//Delete Color
	glDeleteProgram(shaderPrg);
	glDeleteShader(vertShaderData);
	if (tessControlShaderData) {
		glDeleteShader(tessControlShaderData);
	}
	if (tessEvalShaderData) {
		glDeleteShader(tessEvalShaderData);
	}
	if (geometryShaderData) {
		glDeleteShader(geometryShaderData);
	}
	glDeleteShader(fragShaderData);

	//Delete Depth
	glDeleteProgram(depthShaderPrg);
	glDeleteShader(depthVertShaderData);
	if (depthTessControlShaderData) {
		glDeleteShader(depthTessControlShaderData);
	}
	if (depthTessEvalShaderData) {
		glDeleteShader(depthTessEvalShaderData);
	}
	if (depthGeometryShaderData) {
		glDeleteShader(depthGeometryShaderData);
	}
	glDeleteShader(depthFragShaderData);
}