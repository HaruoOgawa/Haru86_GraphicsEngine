#pragma once
#include "GraphicsEngine/Component/Component.h"
#include <memory>

struct BoidsForceData {
    float position[3];
    float velocity[3];
    BoidsForceData() {
        position[0] = 0.0f;
        position[1] = 0.0f;
        position[2] = 0.0f;
        
        velocity[0] = 0.0f;
        velocity[1] = 0.0f;
        velocity[2] = 0.0f;

    }
};

struct BoidsResulrData {
    float velocity[4];
    BoidsResulrData() {
        velocity[0] = 1.0f;
        velocity[1] = 1.0f;
        velocity[2] = 1.0f;
        velocity[3] = 1.0f;
    }
};

class KuraGPGPU :
    public Component
{
public:
    KuraGPGPU(class Object* o);
    ~KuraGPGPU();
    void Start() override;
    void Update() override;
    void ProcessInput(const Uint8* state)const override;
    void Draw();
    friend class KuraArtApp;
private:
    std::unique_ptr<class Material> m_material;
    std::unique_ptr<class Mesh> m_mesh;
    std::unique_ptr<class ComputeBuffer> m_computeBuffer_BoidsResult;
    std::unique_ptr<class ComputeBuffer> m_computeBuffer_BoidsForce;
    std::unique_ptr<class ComputeShader> m_computeShader_force;
    std::unique_ptr<class ComputeShader> m_computeShader_result;
    int num;
    
};

