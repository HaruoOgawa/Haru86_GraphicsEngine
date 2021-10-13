#pragma once

#include <string>
#include <GL/glew.h>

class Material 
{
public:
    Material(std::string vertexShaderName, std::string fragmentShaderName);
    ~Material();
    void LoadShader(std::string vertName,std::string fragName);
    bool CompileShader(std::string shadername,GLenum shaderType,GLuint& outShader);
private :
    GLuint vertShaderData;
    GLuint fragShaderData;
    GLuint shaderPrg;
};

