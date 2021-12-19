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

KuraArtApp::KuraArtApp()
	: BaseApp()
{
}

KuraArtApp::~KuraArtApp() {
	background_obj.reset();
	KuraTerrain_obj.reset();
	audioObj.reset();
}

void KuraArtApp::Start() {
	background_obj = std::make_unique<GameObject>(PrimitiveType::SPHERE,
		"./Assets/Shader/KuraShader/Background.vert",
		"./Assets/Shader/KuraShader/Background.frag");
	background_obj->SetScale(glm::vec3(5000.0));
	std::vector<std::string> texPath = { "./Assets/Resources/TextureData/InkBackground.png" };
	std::vector<std::string> texUniformName = { "_backgroundTex" };
	background_obj->meshComp->material->LoadTextureList(texPath, texUniformName);

	camera_obj = std::make_unique<CameraObject>(CameraType::FIXED_CAMERA);
	camera_obj->SetPosition(glm::vec3(0, 0.0, -3.0));
	Game::GetInstance()->game_camera_instance = camera_obj.get();

	audioObj = std::make_unique<AudioObject>("./Assets/Resources/MusicData/n111.mp3");
	if (audioObj->Initialize()) {
		audioObj->PlayAudio();
	}

	/*std::map<GLenum, std::string> shaders = {
		{GL_VERTEX_SHADER,"./Assets/Shader/KuraShader/KuraTerrain.vert"},
		{GL_TESS_CONTROL_SHADER, "./Assets/Shader/KuraShader/KuraTerrain.tesc"},
		{GL_TESS_EVALUATION_SHADER,"./Assets/Shader/KuraShader/KuraTerrain.tese"},
		{GL_GEOMETRY_SHADER,"./Assets/Shader/KuraShader/KuraTerrain.geom"},
		{GL_FRAGMENT_SHADER,"./Assets/Shader/KuraShader/KuraTerrain.frag"}
	};
	
	KuraTerrain_obj = std::make_unique<GameObject>(PrimitiveType::BOARD,shaders);
	KuraTerrain_obj->SetScale(glm::vec3(5000.0,5000.0,1.0));
	KuraTerrain_obj->SetPosition(glm::vec3(0.0,-1.0,0.0));
	KuraTerrain_obj->SetRotation(glm::quat(glm::vec3(3.14159265/2.0,0.0,0.0)));
	std::vector<std::string> texPath_KuraTerrain_obj = { "./Assets/Resources/TextureData/KuraTerrainHeightMap.png","./Assets/Resources/TextureData/InkBackground.png" };
	std::vector<std::string> texUniformName_KuraTerrain_obj = { "_heightMap","_terrainMap" };
	KuraTerrain_obj->meshComp->material->LoadTextureList(texPath_KuraTerrain_obj, texUniformName_KuraTerrain_obj);

	gpgpu_obj = std::make_unique<Object>();
	gpgpu_obj->AddComponent(std::make_shared<KuraGPGPU>(gpgpu_obj.get()));
	gpgpu_obj->AddComponent(std::make_shared<KuraTrail>(gpgpu_obj.get(),
		static_cast<KuraGPGPU*>(gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraGPGPU).name())))
	));*/

	Game::GetInstance()->renderBoard = std::make_unique<GameObject>(PrimitiveType::BOARD, "./Assets/Shader/VedaStructuredShader/BoardRender.vert", "./Assets/Shader/KuraShader/KuraPostProcess.frag", RenderType::FrameBuffer);

}
void KuraArtApp::Update() {
	//gpgpu_obj->Update();
	
	if (Game::GetInstance()->time>3000) {
		Game::GetInstance()->Restart();
		printf("Game::GetInstance()->time: %f\n", Game::GetInstance()->time);
	}
}

void KuraArtApp::Draw() {
	//static_cast<KuraGPGPU*>(gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraGPGPU).name())))->Draw();
	//static_cast<KuraTrail*>(gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraTrail).name())))->Draw();
}

void KuraArtApp::Timeline(class TimelineObject* timeline) {
	
}

