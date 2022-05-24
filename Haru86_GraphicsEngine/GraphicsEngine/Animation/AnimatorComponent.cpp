#include "AnimatorComponent.h"
#include "GraphicsEngine/Object/Object.h"
#include "GraphicsEngine/Animation/Skeleton.h"
#include "GraphicsEngine/Animation/Pose.h"
#include "GraphicsEngine/Message/Console.h"
#include "GraphicsEngine/Animation/AnimatorComponent.h"

namespace animation {
    AnimatorComponent::AnimatorComponent(Object* o, const std::shared_ptr<Skeleton>& Skeleton):
        Component(o),
        m_Skeleton(Skeleton)
    {
        // ポーズの初期化
        m_CurrentPose = m_Skeleton->GetRestPose();
        m_CurrentPose->GetMatrixPalette(m_PoseMatrix);
    }

    AnimatorComponent::~AnimatorComponent() {
        m_PoseMatrix.clear();
    }

    void AnimatorComponent::Update() {
        //Console::Log("SkinMeshRendererComponent::Update\n");
        // アニメーションの更新
    }

    void AnimatorComponent::Draw() {
    }
    void AnimatorComponent::ProcessInput(const SDL_Event& e) {

    }

    const std::shared_ptr<Skeleton>& AnimatorComponent::GetSkeleton()const {
        return m_Skeleton;
    }

    const std::vector<glm::mat4>& AnimatorComponent::GetPoseMatrix()const {
        return m_PoseMatrix;
    }

    const std::shared_ptr<Pose>& AnimatorComponent::GetCurrentPose()const {
        return m_CurrentPose;
    }
}