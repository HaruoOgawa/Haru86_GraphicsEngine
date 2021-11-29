#include "glTFBinaryReader.h"


glTFBinaryReader::glTFBinaryReader() {

}
glTFBinaryReader::~glTFBinaryReader() {
	vertex.clear();
	subDataVertex.clear();
	normal.clear();
	subDataNormal.clear();
	texcoord.clear();
	subDataTexcoord.clear();

	indices.clear();
	subDataIndices.clear();
}