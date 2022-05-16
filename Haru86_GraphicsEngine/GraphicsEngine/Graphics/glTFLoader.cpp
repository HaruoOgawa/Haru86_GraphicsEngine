#include "glTFLoader.h"
#include "GraphicsEngine/Graphics/Mesh.h"

namespace gltf {
	std::shared_ptr<Mesh> glTFLoader::Load(std::string gltfDataPath) {

		std::shared_ptr<glTFData> data = std::make_shared<glTFData>();
		data->Load(gltfDataPath);

		return data->GetMesh();
	}
}