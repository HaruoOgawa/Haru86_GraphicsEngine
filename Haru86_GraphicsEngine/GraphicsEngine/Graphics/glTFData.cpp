#include "glTFData.h"
#include "GraphicsEngine/Message/Console.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Primitive.h"
#include <memory>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "glTFMesh.h"

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
		tinygltf::Model model;
		std::string err;
		std::string warn;
		bool result = loader.LoadASCIIFromFile(&model, &err, &warn, gltfDataPath);

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
		if (!LoadMesh(model))return false;

		return true;
	}

	bool glTFData::LoadMesh(const tinygltf::Model& model) {
		m_mesh = std::make_shared<Mesh>();

		for (auto mesh : model.meshes) {
			auto index = 0;
			for (auto prim : mesh.primitives) {

				//get vertices
				std::unique_ptr<glTFMesh> reader = std::make_unique<glTFMesh>();

				//vertex
				auto AccessorsIndex = prim.attributes["POSITION"];
				auto BufferViewIndex = model.accessors[AccessorsIndex].bufferView;
				auto ByteLength = model.bufferViews[BufferViewIndex].byteLength;
				auto ByteOffset = model.bufferViews[BufferViewIndex].byteOffset;

				reader->vertex = std::vector<float>(ByteLength / 4, 0.0);
				reader->subDataVertex = std::vector<unsigned char>(ByteLength, 0);

				std::copy(
					model.buffers[0].data.begin() + ByteLength * 0 + ByteOffset,
					model.buffers[0].data.begin() + ByteLength * 1 - 1 + ByteOffset,
					reader->subDataVertex.begin()
				);
				std::memcpy(reader->vertex.data(), reader->subDataVertex.data(), sizeof(float) * reader->vertex.size());

				reader->subDataVertex.clear();

				//normal
				AccessorsIndex = prim.attributes["NORMAL"];
				BufferViewIndex = model.accessors[AccessorsIndex].bufferView;
				ByteLength = model.bufferViews[BufferViewIndex].byteLength;
				ByteOffset = model.bufferViews[BufferViewIndex].byteOffset;

				reader->normal = std::vector<float>(ByteLength / 4, 0.0f);
				reader->subDataNormal = std::vector<unsigned char>(ByteLength, 0);
				std::copy(
					model.buffers[0].data.begin() + ByteLength * 0 + ByteOffset,
					model.buffers[0].data.begin() + ByteLength * 1 - 1 + ByteOffset,
					reader->subDataNormal.begin()
				);
				std::memcpy(reader->normal.data(), reader->subDataNormal.data(), sizeof(float) * reader->normal.size());

				reader->subDataNormal.clear();

				//texcoord
				AccessorsIndex = prim.attributes["TEXCOORD_0"];
				BufferViewIndex = model.accessors[AccessorsIndex].bufferView;
				ByteLength = model.bufferViews[BufferViewIndex].byteLength;
				ByteOffset = model.bufferViews[BufferViewIndex].byteOffset;

				reader->texcoord = std::vector<float>(ByteLength / 4, 0.0f);
				reader->subDataTexcoord = std::vector<unsigned char>(ByteLength, 0);
				std::copy(
					model.buffers[0].data.begin() + ByteLength * 0 + ByteOffset,
					model.buffers[0].data.begin() + ByteLength * 1 - 1 + ByteOffset,
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
				BufferViewIndex = model.accessors[AccessorsIndex].bufferView;
				ByteLength = model.bufferViews[BufferViewIndex].byteLength;
				ByteOffset = model.bufferViews[BufferViewIndex].byteOffset;

				reader->indices = std::vector<unsigned int>(ByteLength / 4, 0);
				reader->subDataIndices = std::vector<unsigned char>(ByteLength, 0);

				std::copy(
					model.buffers[0].data.begin() + ByteLength * 0 + ByteOffset,
					model.buffers[0].data.begin() + ByteLength * 1 - 1 + ByteOffset,
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

	//
	std::shared_ptr<Mesh> glTFData::GetMesh()const {
		return m_mesh;
	}
}