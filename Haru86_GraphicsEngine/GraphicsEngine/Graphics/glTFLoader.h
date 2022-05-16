#pragma once
#include <string>
#include <memory>
#include "glTFData.h"

class Mesh;

namespace gltf {
	static class glTFLoader
	{
	public:
		static std::shared_ptr<Mesh> Load(std::string gltfDataPath);
	};
}

