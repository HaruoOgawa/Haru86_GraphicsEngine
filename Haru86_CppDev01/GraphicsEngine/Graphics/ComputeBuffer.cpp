#include "ComputeBuffer.h"

ComputeBuffer::ComputeBuffer(GLsizeiptr size) {
	CreateBuffer(size);
}

ComputeBuffer::~ComputeBuffer() {

}

void ComputeBuffer::CreateBuffer(GLsizeiptr size) {
	glGenBuffers(1, &ssbo);
	bufferSize = size;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
