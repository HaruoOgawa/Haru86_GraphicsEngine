#pragma once
#include "GraphicsEngine/Component/Component.h"
#include <memory>

class KuraTrail : 
	public Component
{
public:
    KuraTrail(class Object* o,class KuraGPGPU* kuraGPGPU);
    ~KuraTrail();
    void Start() override;
    void Update() override;
    void ProcessInput(const Uint8* state)const override;
    void Draw();
private:
    class KuraGPGPU* kuraGPGPU_instance;
    std::unique_ptr<class Material> m_material;
    std::unique_ptr<class Mesh> m_mesh;
    std::unique_ptr<class ComputeBuffer> m_buffer_trail;
    std::unique_ptr<class ComputeBuffer> m_buffer_node;
    std::unique_ptr<class ComputeBuffer> m_buffer_input;
    std::unique_ptr<class ComputeShader> m_computeShader_NextInputPos;
    std::unique_ptr<class ComputeShader> m_computeShader_NodeInfo;
    int num;
    int nodeSegment;
};

