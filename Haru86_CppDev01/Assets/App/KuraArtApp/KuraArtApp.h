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
    void Timeline(std::shared_ptr<class TimelineObject> timelineObj)  override;
};

