#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <map>

class Material 
{
public:
    Material();
    Material(std::map<GLenum, std::string> shaders);
    Material(std::string vertexShaderName, std::string fragmentShaderName);
    Material(std::string vertexShaderName, std::string tessellationShaderName[2], std::string fragmentShaderName);
    Material(std::string vertexShaderName, std::string geometryShaderName, std::string fragmentShaderName);
    ~Material();
    void LoadShader(std::map<GLenum,std::string> shaders);
    void LoadShader(std::string vertName,std::string fragName);
    void LoadShader(std::string vertName, std::string tessellationShaderName[2],std::string fragName);
    void LoadShader(std::string vertName,std::string geomName,std::string fragName);
    bool CompileShader(std::string shadername,GLenum shaderType,GLuint& outShader);
    void SetActive();
    void UnLoadData();
    void SetMatrixUniform(std::string uniformName,glm::mat4 matrix);
    void SetFloatUniform(std::string uniformName,float val);
    void SetIntUniform(std::string uniformName,int val);
    void SetVec2Uniform(std::string uniformName, glm::vec2 val);
    void SetVec3Uniform(std::string uniformName, glm::vec3 val);
    void SetTexUniform(std::string uniformName, unsigned int val);
    void SetBuffer(std::shared_ptr<class ComputeBuffer> buffer, int bufferIndex);
    void LoadTextureList(std::vector<std::string> texPathList,std::vector<std::string> texUniformNameList);
    void SetActiveTextureList();
    void SetEactiveTextureList();
private :
    GLuint vertShaderData;
    GLuint tessControlShaderData;
    GLuint tessEvalShaderData;
    GLuint geometryShaderData;
    GLuint fragShaderData;
    GLuint shaderPrg;
    std::vector<std::unique_ptr<class Texture>> m_texture_list;
};

