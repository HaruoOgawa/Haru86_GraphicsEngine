#pragma once
#include "../../../GraphicsEngine/Game/Game.h"
#include "../../../GraphicsEngine/App/BaseApp/BaseApp.h"
#include "../../../GraphicsEngine/Graphics/Mesh.h"

#include <vector>
class KuraArtApp :
    public BaseApp
{
public:
    KuraArtApp();
    ~KuraArtApp();
    void Start()  override;
    void Update()  override;
    void Draw() override;
    void Timeline(class TimelineObject* timelineObj)  override;
private :
    std::shared_ptr<class GameObject> background_obj;
    std::shared_ptr<class GameObject> KuraTerrain_obj;
    std::shared_ptr<class AudioObject> audioObj;
    std::shared_ptr<class Object> gpgpu_obj;
    std::unique_ptr<class CameraObject> camera_obj;
};

