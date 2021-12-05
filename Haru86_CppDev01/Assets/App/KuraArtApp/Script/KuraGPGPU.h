#pragma once
#include "GraphicsEngine/Component/Component.h"
#include <memory>
#include <glm/glm.hpp>

struct BoidsForce {
    float velocity[3];
    BoidsForce() {
        velocity[0] = 1.0f;
        velocity[1] = 1.0f;
        velocity[2] = 1.0f;
    }
};

struct BoidsData {
    float position[3];
    float velocity[3];
    BoidsData(float p[3],float v[3]) {
        position[0] = p[0];
        position[1] = p[1];
        position[2] = p[2];

        velocity[0] = v[0];
        velocity[1] = v[1];
        velocity[2] = v[2];

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
    float rand(glm::vec2 st);
    friend class KuraArtApp;
private:
    std::unique_ptr<class Material> m_material;
    std::unique_ptr<class Mesh> m_mesh;
    std::unique_ptr<class ComputeBuffer> m_computeBuffer_BoidsData;
    std::unique_ptr<class ComputeBuffer> m_computeBuffer_BoidsForce;
    std::unique_ptr<class ComputeShader> m_computeShader_force;
    std::unique_ptr<class ComputeShader> m_computeShader_data;
    int num;
    
};

