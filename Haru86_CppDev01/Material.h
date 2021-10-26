#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Material 
{
public:
    Material();
    Material(std::string vertexShaderName, std::string fragmentShaderName);
    ~Material();
    void LoadShader(std::string vertName,std::string fragName);
    bool CompileShader(std::string shadername,GLenum shaderType,GLuint& outShader);
    void SetActive();
    void UnLoadData();
    void SetMatrixUniform(std::string uniformName,glm::mat4 matrix);
    void SetFloatUniform(std::string uniformName,float val);
    void SetVec2Uniform(std::string uniformName, glm::vec2 val);
    void SetTexUniform(std::string uniformName, unsigned int val);
private :
    GLuint vertShaderData;
    GLuint fragShaderData;
    GLuint shaderPrg;
};

