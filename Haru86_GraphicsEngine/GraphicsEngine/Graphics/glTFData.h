#pragma once

#include <string>
#include <memory>
#include <vector>

#include "tiny_gltf.h"

class Mesh;
class TransformComponent;

namespace animation {
	class Pose;
}

namespace gltf {
	class glTFData
	{
		std::shared_ptr<Mesh> m_mesh;
		std::vector<animation::Pose> m_PoseList;
	public:
		glTFData();
		~glTFData();

		//
		bool Load(const std::string& gltfDataPath);
		
		//
		std::shared_ptr<Mesh> GetMesh()const;
	private:
		bool LoadMesh(const tinygltf::Model& model);

		std::shared_ptr<TransformComponent> GetLocalTransform(const tinygltf::Node& node);

		bool LoadPose(const tinygltf::Model& model);
		animation::Pose LoadRestPose(const tinygltf::Model& model);

		std::vector<std::string> LoadJointNames(const tinygltf::Model& model)const;
	};
}