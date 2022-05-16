#include "glTFMesh.h"


glTFMesh::glTFMesh() {

}
glTFMesh::~glTFMesh() {
	vertex.clear();
	subDataVertex.clear();
	normal.clear();
	subDataNormal.clear();
	texcoord.clear();
	subDataTexcoord.clear();

	indices.clear();
	subDataIndices.clear();
}