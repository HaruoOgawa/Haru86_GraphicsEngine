#include "glTFData.h"
#include "GraphicsEngine/Message/Console.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Primitive.h"
#include <memory>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "GraphicsEngine/Animation/TransformTrack.h"

#include "glTFMesh.h"
#include "GraphicsEngine/Component/TransformComponent.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "tiny_gltf.h"

namespace gltf {
	glTFData::glTFData() 
	{
	}

	glTFData::~glTFData() 
	{
	}

	//
	bool glTFData::Load(const std::string& gltfDataPath) {
		// glTFのロード 
		tinygltf::TinyGLTF loader;
		
		std::string err;
		std::string warn;
		bool result = loader.LoadASCIIFromFile(&m_Model, &err, &warn, gltfDataPath);

		// 
		if (!warn.empty()) {
			Console::Log("warn:%s \n", warn.c_str());
			return false;
		}

		if (!err.empty()) {
			Console::Log("err:%s \n", err.c_str());
			return false;
		}

		// 
		if (!result) {
			Console::Log("glTF Load Error...");
			return false;
		}

		// 解析
		if (!LoadMesh())return false;
		if (!LoadPose())return false;

		return true;
	}

	bool glTFData::LoadMesh() {
		m_mesh = std::make_shared<Mesh>();

		for (auto mesh : m_Model.meshes) {
			auto index = 0;
			for (auto prim : mesh.primitives) {

				//get vertices
				std::unique_ptr<glTFMesh> reader = std::make_unique<glTFMesh>();

				//vertex
				auto AccessorsIndex = prim.attributes["POSITION"];
				auto BufferViewIndex = m_Model.accessors[AccessorsIndex].bufferView;
				auto ByteLength = m_Model.bufferViews[BufferViewIndex].byteLength;
				auto ByteOffset = m_Model.bufferViews[BufferViewIndex].byteOffset;

				reader->vertex = std::vector<float>(ByteLength / 4, 0.0);
				reader->subDataVertex = std::vector<unsigned char>(ByteLength, 0);

				std::copy(
					m_Model.buffers[0].data.begin() + ByteLength * 0 + ByteOffset,
					m_Model.buffers[0].data.begin() + ByteLength * 1 - 1 + ByteOffset,
					reader->subDataVertex.begin()
				);
				std::memcpy(reader->vertex.data(), reader->subDataVertex.data(), sizeof(float) * reader->vertex.size());

				reader->subDataVertex.clear();

				//normal
				AccessorsIndex = prim.attributes["NORMAL"];
				BufferViewIndex = m_Model.accessors[AccessorsIndex].bufferView;
				ByteLength = m_Model.bufferViews[BufferViewIndex].byteLength;
				ByteOffset = m_Model.bufferViews[BufferViewIndex].byteOffset;

				reader->normal = std::vector<float>(ByteLength / 4, 0.0f);
				reader->subDataNormal = std::vector<unsigned char>(ByteLength, 0);
				std::copy(
					m_Model.buffers[0].data.begin() + ByteLength * 0 + ByteOffset,
					m_Model.buffers[0].data.begin() + ByteLength * 1 - 1 + ByteOffset,
					reader->subDataNormal.begin()
				);
				std::memcpy(reader->normal.data(), reader->subDataNormal.data(), sizeof(float) * reader->normal.size());

				reader->subDataNormal.clear();

				//texcoord
				AccessorsIndex = prim.attributes["TEXCOORD_0"];
				BufferViewIndex = m_Model.accessors[AccessorsIndex].bufferView;
				ByteLength = m_Model.bufferViews[BufferViewIndex].byteLength;
				ByteOffset = m_Model.bufferViews[BufferViewIndex].byteOffset;

				reader->texcoord = std::vector<float>(ByteLength / 4, 0.0f);
				reader->subDataTexcoord = std::vector<unsigned char>(ByteLength, 0);
				std::copy(
					m_Model.buffers[0].data.begin() + ByteLength * 0 + ByteOffset,
					m_Model.buffers[0].data.begin() + ByteLength * 1 - 1 + ByteOffset,
					reader->subDataTexcoord.begin()
				);
				std::memcpy(reader->texcoord.data(), reader->subDataTexcoord.data(), sizeof(float) * reader->texcoord.size());

				reader->subDataTexcoord.clear();

				//set vertices data
				std::vector<std::vector<float>> vertices;
				vertices.push_back(reader->vertex);
				reader->vertex.clear();
				vertices.push_back(reader->normal);
				reader->normal.clear();
				vertices.push_back(reader->texcoord);
				reader->texcoord.clear();

				std::vector<int> dimention;
				dimention.push_back(3);
				dimention.push_back(3);
				dimention.push_back(2);

				////get indices///////////////////////////////////

				AccessorsIndex = prim.indices;
				BufferViewIndex = m_Model.accessors[AccessorsIndex].bufferView;
				ByteLength = m_Model.bufferViews[BufferViewIndex].byteLength;
				ByteOffset = m_Model.bufferViews[BufferViewIndex].byteOffset;

				reader->indices = std::vector<unsigned int>(ByteLength / 4, 0);
				reader->subDataIndices = std::vector<unsigned char>(ByteLength, 0);

				std::copy(
					m_Model.buffers[0].data.begin() + ByteLength * 0 + ByteOffset,
					m_Model.buffers[0].data.begin() + ByteLength * 1 - 1 + ByteOffset,
					reader->subDataIndices.begin()
				);
				std::memcpy(reader->indices.data(), reader->subDataIndices.data(), sizeof(unsigned int) * reader->indices.size());
				reader->subDataIndices.clear();

				reader->mainDataIndices = std::vector<unsigned short>(reader->indices.begin(), reader->indices.end());

				//この辺でPrimitiveにデータを渡す
				std::shared_ptr<Primitive> m_prim = std::make_shared<Primitive>(vertices, dimention, reader->mainDataIndices);
				m_mesh->SetPrimitive(m_prim);

				//すべてのメモリを一応解放
				vertices.clear();
				dimention.clear();
				reader->indices.clear();
				reader->mainDataIndices.clear();

				index++;
			}

		}

		return true;
	}

	bool glTFData::LoadPose() {
		//const auto RestPose = LoadRestPose(m_Model);
		return true;
	}

	animation::Pose glTFData::LoadRestPose() {
		unsigned int boneCount = static_cast<unsigned int>(m_Model.nodes.size());
		animation::Pose result(boneCount);

		for (unsigned int i = 0; i < boneCount;i++) {
			tinygltf::Node node = m_Model.nodes[i];
			result.SetLocalTransform(i, GetLocalTransform(node));

			int parent = i;
			for (const auto& child : node.children) {
				result.SetParent(child, parent);
			}
			
		}

		return result;
	}

	std::vector<std::string> glTFData::LoadJointNames()const {
		unsigned int boneCount = static_cast<unsigned int>(m_Model.nodes.size());
		std::vector<std::string> result(boneCount,"Not Set");

		for (unsigned int i = 0; i < boneCount;i++) {
			tinygltf::Node node = m_Model.nodes[i];

			if (node.name.empty()) {
				result[i] = "EMPTY NODE";
			}
			else {
				result[i] = node.name;
			}
		}

		return result;
	}

	std::shared_ptr<TransformComponent> glTFData::GetLocalTransform(const tinygltf::Node& node) {
		std::shared_ptr<TransformComponent> result = std::make_shared<TransformComponent>();

		// mmatrix
		/*if (node.matrix.size() == 16) {
			glm::mat4 mmatrix = glm::mat4();
			for (unsigned int n = 0; n < node.matrix.size();n++) {
				const auto& val = node.matrix[n];
				unsigned int firstIndex = static_cast<unsigned int>(n / 4.0); // 0 to 3
				int secondIndex = static_cast<unsigned int>(n - firstIndex * 4.0);

				mmatrix[firstIndex][secondIndex] = val;
			}

		}*/

		// position
		if (node.translation.size() > 0) {
			result->SetPosition(glm::vec3(node.translation[0], node.translation[1], node.translation[2]));
		}

		// rotation
		if (node.rotation.size() > 0) {
			result->SetRotation(glm::quat(glm::vec3(node.rotation[0], node.rotation[1], node.rotation[2])));
		}

		// scale
		if (node.scale.size() > 0) {
			result->SetScale(glm::vec3(node.scale[0], node.scale[1], node.scale[2]));
		}

		return result;
	}

	void glTFData::GetScalarValues(std::vector<float>& out, unsigned int compCount, const tinygltf::Accessor& inAccessor) {
		out.resize(inAccessor.count * compCount);
		int BufferIndex=m_Model.bufferViews[inAccessor.bufferView].buffer;
		std::memcpy(&m_Model.buffers[BufferIndex].data[0], &out[0], sizeof(float) * inAccessor.count * compCount);
	}

	std::vector<animation::Clip> glTFData::LoadAnimationClips() {
		//
		unsigned int numClips = m_Model.animations.size();
		unsigned int numNodes = m_Model.nodes.size();

		std::vector<animation::Clip> result;
		result.resize(numClips);

		//
		for (unsigned int i = 0; i < numClips;i++) {
			result[i].SetName(m_Model.animations[i].name);

			unsigned int numChannels = m_Model.animations[i].channels.size();

			for (unsigned int j = 0; j < numChannels;j++) {
				tinygltf::AnimationChannel& channel = m_Model.animations[i].channels[j];

				tinygltf::Node target = m_Model.nodes[channel.target_node];

				int nodeId = channel.target_node;

				if (channel.target_path=="translation") {
					animation::VectorTrack& track = result[i][nodeId].GetPositionTrack();
					TrackFromChannel<glm::vec3,3>(track, channel,m_Model.animations[i].samplers);
				}else if (channel.target_path == "scale") {
					animation::VectorTrack& track = result[i][nodeId].GetScaleTrack();
					TrackFromChannel<glm::vec3, 3>(track, channel, m_Model.animations[i].samplers);
				}else if (channel.target_path == "rotation") {
					animation::QuaternionTrack& track = result[i][nodeId].GetRotationTrack();
					TrackFromChannel<glm::quat, 4>(track, channel, m_Model.animations[i].samplers);
				}
			}

			//
			result[i].RecalculateDuration();
		}

		//
		return result;
	}
	//
	std::shared_ptr<Mesh> glTFData::GetMesh()const {
		return m_mesh;
	}
}
