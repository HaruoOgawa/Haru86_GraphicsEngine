#pragma once
#include <string>
#include <memory>
#include "glTFData.h"

class Mesh;

namespace gltf {
	static class glTFLoader
	{
	public:
		static std::shared_ptr<glTFData> Load(std::string gltfDataPath);
	};
}

