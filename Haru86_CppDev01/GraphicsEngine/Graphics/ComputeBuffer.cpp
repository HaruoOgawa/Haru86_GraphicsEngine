#include "ComputeBuffer.h"

ComputeBuffer::ComputeBuffer(GLsizeiptr size) {
	CreateBuffer(size);
}

ComputeBuffer::~ComputeBuffer() {

}

void ComputeBuffer::CreateBuffer(GLsizeiptr size) {
	glGenBuffers(1, &ssbo);
	bufferSize = size;
}

template<typename T>
void ComputeBuffer::SetData(T data) {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	//ここでデータをセット
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);
	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}