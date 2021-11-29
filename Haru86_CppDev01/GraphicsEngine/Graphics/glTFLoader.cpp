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
		//model.meshes 1ŒÂ
		//model.meshes[0].primitives 3ŒÂ
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
				
				/*float pos[22836];
				std::vector<unsigned char> subData(22836,0);
				std::copy(
					model.buffers[0].data.begin() + 22836*index, 
					model.buffers[0].data.begin() +22836 * (index+1)-1,
					subData.begin()
				);
				std::memcpy(&pos, subData.data(), sizeof(pos));*/

				index++;
			}
			
		}
		

		printf("model.buffers[0].data.size():%d \n", model.buffers[0].data.size());
		printf("model.buffers[0].data[0]:%u \n", model.buffers[0].data[0]);

	}

	


	return std::move(m_mesh);
}