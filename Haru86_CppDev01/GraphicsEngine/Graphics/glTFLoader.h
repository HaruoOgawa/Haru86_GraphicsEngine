#pragma once
#include <string>
#include <memory>

static class glTFLoader
{
public:
	static std::unique_ptr<class Mesh> Load(std::string gltfDataPath);
};

