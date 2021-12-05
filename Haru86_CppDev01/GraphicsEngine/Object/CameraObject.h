#pragma once
#include "Object.h"
#include <memory>

enum CameraType
{
    FIXED_CAMERA,
    FPS_CAMERA,
    FOLLOW_CAMERA
};

class CameraObject :
    public Object
{
public:
    CameraObject(CameraType cameraType);
    ~CameraObject();
    void Update() override;
private:
    class CameraComponent* m_cameraComponent;
};

