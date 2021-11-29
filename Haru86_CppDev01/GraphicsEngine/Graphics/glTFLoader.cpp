#include "glTFLoader.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Primitive.h"
#include <memory>
#include <cstring>

#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_USE_CPP14
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

#include "GraphicsEngine/Graphics/glTFBinaryReader.h"


std::unique_ptr<Mesh> glTFLoader::Load(std::string gltfDataPath) {

	tinygltf::TinyGLTF loader;
	tinygltf::Model model;
	std::string err;
	std::string warn;
	bool result = loader.LoadASCIIFromFile(&model, &err, &warn, gltfDataPath);
	std::unique_ptr<Mesh> m_mesh = std::make_unique<Mesh>();

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
		printf("model.meshes.size():%d \n",static_cast<int>(model.meshes.size()));
		printf("model.meshes[0].primitives.size():%d \n",static_cast<int>(model.meshes[0].primitives.size()));

		for (auto mesh : model.meshes) {
			auto index = 0;
			for (auto prim:mesh.primitives) {
				
				//get vertices
				std::unique_ptr<glTFBinaryReader> reader = std::make_unique<glTFBinaryReader>();
				
				//vertex
				reader->vertex = std::vector<float>(5709, 0.0);
				reader->subDataVertex = std::vector<unsigned char>(22836, 0);

				std::copy(
					model.buffers[0].data.begin() + 22836*index, 
					model.buffers[0].data.begin() +22836 * (index+1)-1,
					reader->subDataVertex.begin()
				);
				std::memcpy(reader->vertex.data(), reader->subDataVertex.data(), sizeof(float)* reader->vertex.size());
				reader->subDataVertex.clear();

				//normal
				reader->normal=std::vector<float>(5709, 0.0f);
				reader->subDataNormal =std::vector<unsigned char>(22836, 0);
				std::copy(
					model.buffers[0].data.begin() + 22836 * index+ 68508,
					model.buffers[0].data.begin() + 22836 * (index + 1) - 1+ 68508,
					reader->subDataNormal.begin()
				);
				std::memcpy(reader->normal.data(), reader->subDataNormal.data(), sizeof(float)* reader->normal.size());

				reader->subDataNormal.clear();

				//texcoord
				reader->texcoord =std::vector<float>(3806, 0.0f);
				reader->subDataTexcoord =std::vector<unsigned char>(15224, 0);
				std::copy(
					model.buffers[0].data.begin() + 15224 * index+ 137016,
					model.buffers[0].data.begin() + 15224 * (index + 1) - 1+ 137016,
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

				//std::vector<int> indices = model.meshes[0].primitives[index].indices;
				////get indices
				reader->indices = std::vector<int>(192, 0);
				reader->subDataIndices = std::vector<unsigned char>(768, 0);

				std::copy(
					model.buffers[0].data.begin() + 768 * index+ 344292,
					model.buffers[0].data.begin() + 768 * (index + 1) - 1+ 344292,
					reader->subDataIndices.begin()
				);
				std::memcpy(reader->indices.data(), reader->subDataIndices.data(), sizeof(int)* reader->indices.size());
				reader->subDataIndices.clear();

				//Ç±ÇÃï”Ç≈PrimitiveÇ…ÉfÅ[É^ÇìnÇ∑
				std::unique_ptr<Primitive> m_prim = std::make_unique<Primitive>(vertices,dimention,reader->indices);
				m_mesh->m_primitives.push_back(std::move(m_prim));

				//Ç∑Ç◊ÇƒÇÃÉÅÉÇÉäÇàÍâûâï˙
				vertices.clear();
				dimention.clear();
				reader->indices.clear();

				index++;

				printf("Load Primitive\n");
				printf("_________________________________________________________________________\n");
			}
			
		}
		
	}

	return std::move(m_mesh);
}