#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>

class ComputeBuffer
{
public:
	ComputeBuffer(GLsizeiptr size);
	~ComputeBuffer();
	void SetData();
private:
	void CreateBuffer(GLsizeiptr size);
	GLuint ssbo;
	GLsizeiptr bufferSize;
};

