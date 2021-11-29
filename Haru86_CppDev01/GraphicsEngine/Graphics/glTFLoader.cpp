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
		printf("Success!! Load glTF\n");
		//model.meshes 1å¬
		//model.meshes[0].primitives 3å¬
		//model.meshes[0].primitives[0].attributes; 
		//model.meshes[0].primitives[0].indices;
		
		for (auto mesh : model.meshes) {
			auto index = 0;
			for (auto prim:mesh.primitives) {
				//std::unique_ptr<Primitive> m_prim = std::make_unique<Primitive>(prim.attributes, prim.indices);
				//m_mesh->m_primitives.push_back(std::move(m_prim));
				printf("_________________________________________________________________________\n");
				printf("prim.attributes[JOINTS_0]:%d \n", static_cast<int>(prim.attributes["JOINTS_0"]));
				printf("prim.attributes[NORMAL]:%d \n", static_cast<int>(prim.attributes["NORMAL"]));
				printf("prim.attributes[POSITION]:%d \n", static_cast<int>(prim.attributes["POSITION"]));
				printf("prim.attributes[TEXCOORD_0]:%d \n", static_cast<int>(prim.attributes["TEXCOORD_0"]));
				printf("prim.attributes[WEIGHTS_0]:%d \n", static_cast<int>(prim.attributes["WEIGHTS_0"]));
				printf("_________________________________________________________________________\n");
				
				std::unique_ptr<glTFBinaryReader> reader = std::make_unique<glTFBinaryReader>();
				//////////////////////////////////////////////////////////////////////////
				reader->vertex = std::vector<float>(22836, 0.0);
				reader->subDataVertex = std::vector<unsigned char>(22836, 0);

				std::copy(
					model.buffers[0].data.begin() + 22836*index, 
					model.buffers[0].data.begin() +22836 * (index+1)-1,
					reader->subDataVertex.begin()
				);
				std::memcpy(reader->vertex.data(), reader->subDataVertex.data(), sizeof(reader->vertex));
				reader->subDataVertex.clear();

				//////////////////////////////////////////////////////////////////////////
				reader->normal=std::vector<float>(22836, 0.0f);
				reader->subDataNormal =std::vector<unsigned char>(22836, 0);
				std::copy(
					model.buffers[0].data.begin() + 22836 * index+ 68508,
					model.buffers[0].data.begin() + 22836 * (index + 1) - 1+ 68508,
					reader->subDataNormal.begin()
				);
				std::memcpy(reader->normal.data(), reader->subDataNormal.data(), sizeof(reader->normal));

				reader->subDataNormal.clear();

				//////////////////////////////////////////////////////////////////////////
				reader->texcoord =std::vector<float>(15224, 0.0f);
				reader->subDataTexcoord =std::vector<unsigned char>(15224, 0);
				std::copy(
					model.buffers[0].data.begin() + 15224 * index+ 137016,
					model.buffers[0].data.begin() + 15224 * (index + 1) - 1+ 137016,
					reader->subDataTexcoord.begin()
				);
				std::memcpy(reader->texcoord.data(), reader->subDataTexcoord.data(), sizeof(reader->texcoord));

				reader->subDataTexcoord.clear();

				//////////////////////////////////////////////////////////////////////////
				
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
				printf("model.meshes[0].primitives[index].indices: %d \n", static_cast<int>(model.meshes[0].primitives[index].indices));
			
				//Ç±ÇÃï”Ç≈PrimitiveÇ…ÉfÅ[É^ÇìnÇ∑

				//Ç∑Ç◊ÇƒÇÃÉÅÉÇÉäÇàÍâûâï˙
				vertices.clear();
				dimention.clear();
				//indices.clear();

				index++;
			}
			
		}
		
	}

	return std::move(m_mesh);
}