#pragma once
#include "../../../GraphicsEngine/GraphicsMain/GraphicsMain.h"
#include "../../../GraphicsEngine/App/BaseApp/BaseApp.h"
#include <memory>

class GameObject;

class GraphicsLearning :
    public BaseApp
{
public:
    GraphicsLearning();
    ~GraphicsLearning();
    void Start()  override;
    void Update()  override;
    void Draw() override;
    void Timeline(class TimelineObject* timelineObj)  override;
private:
    std::shared_ptr<GameObject> m_GraphObj;
    std::shared_ptr<class CameraObject> cam_obj;
};

