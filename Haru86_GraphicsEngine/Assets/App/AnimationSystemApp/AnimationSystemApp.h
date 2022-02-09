#pragma once
#include "../../../GraphicsEngine/App/BaseApp/BaseApp.h"
class AnimationSystemApp :
    public BaseApp
{
public:
    AnimationSystemApp();
    virtual ~AnimationSystemApp();
    void Start()  override;
    void Update()  override;
    void Draw() override;
    void Timeline(class TimelineObject* timelineObj)  override;
};

