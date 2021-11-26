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
