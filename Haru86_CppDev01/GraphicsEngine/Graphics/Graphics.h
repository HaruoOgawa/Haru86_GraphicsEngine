#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

static class Graphics
{
public:
	static void DrawInstancedWithMesh(class Mesh* mesh,int count);
	static void Dispatch(class ComputeShader cs,int xGroupNum,int yGroupNum,int zGroupNum);
};

