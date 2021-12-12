#include "KuraArtApp.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Object/TimelineObject.h"
#include "GraphicsEngine/Component/TimelineComponent.h"
#include "GraphicsEngine/Component/UIComponent.h"
#include "GraphicsEngine/Component/MeshRendererComponent.h"
#include "GraphicsEngine/Component/RectTransformComponent.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Object/AudioObject.h"
#include "GraphicsEngine/Component/AudioSourceComponent.h"
#include <memory>
#include <string>
#include "GraphicsEngine/Object/Object.h"
#include "./Assets/App/KuraArtApp/Script/KuraGPGPU.h"
#include "./Assets/App/KuraArtApp/Script/KuraTrail.h"
#include "GraphicsEngine/Object/CameraObject.h"
#include <GL/glew.h>

namespace Kura{
	std::unique_ptr<GameObject> background_obj;
	std::unique_ptr<GameObject> KuraTerrain_obj;
	std::unique_ptr<AudioObject> audioObj;
	std::unique_ptr<Object> gpgpu_obj;
	std::unique_ptr<CameraObject> camera_obj;
}

KuraArtApp::KuraArtApp()
{
	
}

KuraArtApp::~KuraArtApp() {

}

void KuraArtApp::Start() {
	Kura::background_obj = std::make_unique<GameObject>(PrimitiveType::SPHERE,
		"./Assets/Shader/KuraShader/Background.vert",
		"./Assets/Shader/KuraShader/Background.frag");
	Kura::background_obj->SetScale(glm::vec3(5000.0));
	std::vector<std::string> texPath = { "./Assets/Resources/TextureData/InkBackground.png" };
	std::vector<std::string> texUniformName = { "_backgroundTex" };
	Kura::background_obj->meshComp->material->LoadTextureList(texPath, texUniformName);

	Kura::camera_obj = std::make_unique<CameraObject>(CameraType::FIXED_CAMERA);
	//Kura::camera_obj->SetPosition(glm::vec3(0, 10.0, -10.0));
	Kura::camera_obj->SetPosition(glm::vec3(0, 0.0, -3.0));

	Kura::audioObj = std::make_unique<AudioObject>("./Assets/Resources/MusicData/n111.mp3");
	if (Kura::audioObj->Initialize()) {
		//Kura::audioObj->PlayAudio();
	}

	std::map<GLenum, std::string> shaders = {
		{GL_VERTEX_SHADER,"./Assets/Shader/KuraShader/KuraTerrain.vert"},
		{GL_TESS_CONTROL_SHADER, "./Assets/Shader/KuraShader/KuraTerrain.tesc"},
		{GL_TESS_EVALUATION_SHADER,"./Assets/Shader/KuraShader/KuraTerrain.tese"},
		{GL_GEOMETRY_SHADER,"./Assets/Shader/KuraShader/KuraTerrain.geom"},
		{GL_FRAGMENT_SHADER,"./Assets/Shader/KuraShader/KuraTerrain.frag"}
	};
	
	Kura::KuraTerrain_obj = std::make_unique<GameObject>(PrimitiveType::BOARD,shaders);
	//Kura::KuraTerrain_obj->SetScale(glm::vec3(5.0,5.0,1.0));
	Kura::KuraTerrain_obj->SetScale(glm::vec3(5000.0,5000.0,1.0));
	Kura::KuraTerrain_obj->SetPosition(glm::vec3(0.0,-1.0,0.0));
	Kura::KuraTerrain_obj->SetRotation(glm::quat(glm::vec3(3.14159265/2.0,0.0,0.0)));
	std::vector<std::string> texPath_KuraTerrain_obj = { "./Assets/Resources/TextureData/KuraTerrainHeightMap.png" };
	std::vector<std::string> texUniformName_KuraTerrain_obj = { "_heightMap" };
	Kura::KuraTerrain_obj->meshComp->material->LoadTextureList(texPath_KuraTerrain_obj, texUniformName_KuraTerrain_obj);

	Kura::gpgpu_obj = std::make_unique<Object>();
	Kura::gpgpu_obj->AddComponent(new KuraGPGPU(Kura::gpgpu_obj.get()));
	Kura::gpgpu_obj->AddComponent(new KuraTrail(Kura::gpgpu_obj.get(),
		static_cast<KuraGPGPU*>(Kura::gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraGPGPU).name())))
	));


}
void KuraArtApp::Update() {
	Kura::gpgpu_obj->Update();
}

void KuraArtApp::Draw() {
	static_cast<KuraGPGPU*>(Kura::gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraGPGPU).name())))->Draw();
	static_cast<KuraTrail*>(Kura::gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraTrail).name())))->Draw();
	
}

void KuraArtApp::Timeline(TimelineObject* timeline) {
	
}

