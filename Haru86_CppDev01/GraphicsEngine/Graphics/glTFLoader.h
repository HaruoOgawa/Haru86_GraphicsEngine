#pragma once
#include <string>
#include <memory>

static class glTFLoader
{
public:
	static std::shared_ptr<class Mesh> Load(std::string gltfDataPath);
};

