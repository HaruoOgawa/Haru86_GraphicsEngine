#include "glTFLoader.h"
#include "GraphicsEngine/Graphics/Mesh.h"

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
	}

	std::unique_ptr<Mesh> m_mesh=std::make_unique<Mesh>();


	return std::move(m_mesh);
}