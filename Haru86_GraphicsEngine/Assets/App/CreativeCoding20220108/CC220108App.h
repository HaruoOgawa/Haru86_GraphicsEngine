#pragma once
#include "../../../GraphicsEngine/Game/Game.h"
#include "../../../GraphicsEngine/App/BaseApp/BaseApp.h"
#include <memory>
class CC220108App :
    public BaseApp
{
public:
    CC220108App();
    ~CC220108App();
    void Start()  override;
    void Update()  override;
    void Draw() override;
    void Timeline(class TimelineObject* timelineObj)  override;
private:
    std::unique_ptr<class GameObject> ins_cubes;
    std::unique_ptr<class CameraObject> cam_obj;
};

