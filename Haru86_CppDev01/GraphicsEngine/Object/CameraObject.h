#pragma once
#include "Object.h"
#include <memory>

enum class CameraType
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
    CameraType m_cameraType;
private:
    class CameraComponent* m_cameraComponent;
};

