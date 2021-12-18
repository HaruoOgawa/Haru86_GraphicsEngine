#include "glTFLoader.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Primitive.h"
#include <memory>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_USE_CPP14
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

#include "GraphicsEngine/Graphics/glTFBinaryReader.h"


std::shared_ptr<Mesh> glTFLoader::Load(std::string gltfDataPath) {

	tinygltf::TinyGLTF loader;
	tinygltf::Model model;
	std::string err;
	std::string warn;
	bool result = loader.LoadASCIIFromFile(&model, &err, &warn, gltfDataPath);
	
	std::shared_ptr<Mesh> m_mesh = std::make_unique<Mesh>();
	glm::mat4 translationMatirx = glm::translate(glm::mat4(1.0f), glm::vec3(
		0.0,//-2.5335649919168424e-14,
		0.0,//1.102462761082279e-7,
		0.0//-7.312606697951196e-8
	));
	//glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat(glm::vec4(-2.15842363e-7, -0.758994639, 0.6510969, -4.371139e-8)));
	//glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(4941.836, 4941.83838, 4941.83838));
	m_mesh->localMatrix = translationMatirx; // *rotationMatrix* scaleMatrix;

	if (!warn.empty()) {
		printf("warn:%s \n", warn.c_str());
	}

	if (!err.empty()) {
		printf("err:%s \n",err.c_str());
	}

	if (!result) {
		printf("glTF Load Error...");
	}
	else {
		
		for (auto mesh : model.meshes) {
			auto index = 0;
			for (auto prim:mesh.primitives) {
				
				//get vertices
				std::unique_ptr<glTFBinaryReader> reader = std::make_unique<glTFBinaryReader>();
				
				//vertex
				auto AccessorsIndex = prim.attributes["POSITION"];
				auto BufferViewIndex = model.accessors[AccessorsIndex].bufferView;
				auto ByteLength = model.bufferViews[BufferViewIndex].byteLength;
				auto ByteOffset = model.bufferViews[BufferViewIndex].byteOffset;

				reader->vertex = std::vector<float>(ByteLength / 4, 0.0);
				reader->subDataVertex = std::vector<unsigned char>(ByteLength, 0);

				std::copy(
					model.buffers[0].data.begin() + ByteLength *0+ ByteOffset,
					model.buffers[0].data.begin() + ByteLength * 1-1+ ByteOffset,
					reader->subDataVertex.begin()
				);
				std::memcpy(reader->vertex.data(), reader->subDataVertex.data(), sizeof(float)* reader->vertex.size());
				
				reader->subDataVertex.clear();

				//normal
				AccessorsIndex = prim.attributes["NORMAL"];
				BufferViewIndex = model.accessors[AccessorsIndex].bufferView;
				ByteLength = model.bufferViews[BufferViewIndex].byteLength;
				ByteOffset = model.bufferViews[BufferViewIndex].byteOffset;

				reader->normal=std::vector<float>(ByteLength/ 4, 0.0f);
				reader->subDataNormal =std::vector<unsigned char>(ByteLength, 0);
				std::copy(
					model.buffers[0].data.begin() + ByteLength * 0+ ByteOffset,
					model.buffers[0].data.begin() + ByteLength * 1 - 1+ ByteOffset,
					reader->subDataNormal.begin()
				);
				std::memcpy(reader->normal.data(), reader->subDataNormal.data(), sizeof(float)* reader->normal.size());

				reader->subDataNormal.clear();

				//texcoord
				AccessorsIndex = prim.attributes["TEXCOORD_0"];
				BufferViewIndex = model.accessors[AccessorsIndex].bufferView;
				ByteLength = model.bufferViews[BufferViewIndex].byteLength;
				ByteOffset = model.bufferViews[BufferViewIndex].byteOffset;

				reader->texcoord =std::vector<float>(ByteLength/ 4, 0.0f);
				reader->subDataTexcoord =std::vector<unsigned char>(ByteLength, 0);
				std::copy(
					model.buffers[0].data.begin() + ByteLength * 0+ ByteOffset,
					model.buffers[0].data.begin() + ByteLength * 1 - 1+ ByteOffset,
					reader->subDataTexcoord.begin()
				);
				std::memcpy(reader->texcoord.data(), reader->subDataTexcoord.data(), sizeof(float)* reader->texcoord.size());

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

				reader->indices = std::vector<unsigned int>(ByteLength /4, 0);
				reader->subDataIndices = std::vector<unsigned char>(ByteLength, 0);

				std::copy(
					model.buffers[0].data.begin() + ByteLength * 0+ ByteOffset,
					model.buffers[0].data.begin() + ByteLength * 1 - 1+ ByteOffset,
					reader->subDataIndices.begin()
				);
				std::memcpy(reader->indices.data(), reader->subDataIndices.data(), sizeof(unsigned int)* reader->indices.size());
				reader->subDataIndices.clear();

				reader->mainDataIndices = std::vector<unsigned short>(reader->indices.begin(),reader->indices.end());

				//Ç±ÇÃï”Ç≈PrimitiveÇ…ÉfÅ[É^ÇìnÇ∑
				std::unique_ptr<Primitive> m_prim = std::make_unique<Primitive>(vertices,dimention,reader->mainDataIndices);
				m_mesh->m_primitives.push_back(std::move(m_prim));

				//Ç∑Ç◊ÇƒÇÃÉÅÉÇÉäÇàÍâûâï˙
				vertices.clear();
				dimention.clear();
				reader->indices.clear();
				reader->mainDataIndices.clear();

				index++;

			}
			
		}
		
	}

	return m_mesh;
}