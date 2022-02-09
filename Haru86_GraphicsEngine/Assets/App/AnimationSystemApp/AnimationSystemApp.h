#pragma once
#include "../../../GraphicsEngine/App/BaseApp/BaseApp.h"
#include <memory>

class GameObject;

class AnimationSystemApp :
    public BaseApp
{
    std::unique_ptr<GameObject> m_Plane;
    std::unique_ptr<GameObject> m_Ceiling;
public:
    AnimationSystemApp();
    virtual ~AnimationSystemApp();
    void Start()  override;
    void Update()  override;
    void Draw() override;
    void Timeline(class TimelineObject* timelineObj)  override;

private:

};

