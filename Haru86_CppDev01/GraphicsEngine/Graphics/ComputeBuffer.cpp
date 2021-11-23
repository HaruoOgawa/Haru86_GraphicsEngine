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

void ComputeBuffer::SetData() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	//ここでデータをセット

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}