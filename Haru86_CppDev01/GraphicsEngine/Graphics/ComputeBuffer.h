#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>

class ComputeBuffer
{
public:
	ComputeBuffer(GLsizeiptr size);
	~ComputeBuffer();
	template<typename T>
	void SetData(T data);
	friend class ComputeShader;
private:
	void CreateBuffer(GLsizeiptr size);
	GLuint ssbo;
	GLsizeiptr bufferSize;
};

