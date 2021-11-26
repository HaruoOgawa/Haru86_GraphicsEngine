#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

class ComputeBuffer
{
public:
	ComputeBuffer(GLsizeiptr size);
	~ComputeBuffer();
	template<typename T>
	void SetData(T data) {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data.data()), data.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	template<typename T>
	void GetBufferData(T *data,int offset) {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(data),data);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	friend class ComputeShader;
private:
	void CreateBuffer(GLsizeiptr size);
	GLuint ssbo;
	GLsizeiptr bufferSize;
};

