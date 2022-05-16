#pragma once

#include <string>
#include <memory>
#include "tiny_gltf.h"

class Mesh;

namespace gltf {
	class glTFData
	{
		std::shared_ptr<Mesh> m_mesh;
	public:
		glTFData();
		~glTFData();

		//
		bool Load(const std::string& gltfDataPath);
		
		//
		std::shared_ptr<Mesh> GetMesh()const;
	private:
		bool LoadMesh(const tinygltf::Model& model);
	};
}