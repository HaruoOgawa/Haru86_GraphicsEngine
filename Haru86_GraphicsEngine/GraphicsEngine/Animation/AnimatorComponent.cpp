#include "AnimatorComponent.h"
#include "GraphicsEngine/Object/Object.h"
#include "GraphicsEngine/GraphicsMain/GraphicsMain.h"
#include "GraphicsEngine/Animation/Skeleton.h"
#include "GraphicsEngine/Animation/Pose.h"
#include "GraphicsEngine/Animation/Clip.h"
#include "GraphicsEngine/Message/Console.h"
#include "GraphicsEngine/Animation/AnimatorComponent.h"

namespace animation {
    //AnimatorComponent::AnimatorComponent(Object* o, const std::shared_ptr<Skeleton>& Skeleton):
    AnimatorComponent::AnimatorComponent(Object* o, const std::shared_ptr<Skeleton>& Skeleton, const std::vector<std::shared_ptr<animation::Clip>>& AnimationClipList):
        Component(o),
        m_Skeleton(Skeleton),
        m_AnimationClipList(AnimationClipList),
        m_PlaybackTime(0.0f)
    {
        // ポーズの初期化
        m_CurrentPose = m_Skeleton->GetRestPose();
        m_CurrentPose->GetMatrixPalette(m_PoseMatrix);
    }

    AnimatorComponent::~AnimatorComponent() {
        m_PoseMatrix.clear();
    }

    void AnimatorComponent::Update() {
        //Console::Log("SkinMeshRendererComponent::Update / m_AnimationClipList.size(): %d\n", m_AnimationClipList.size());
        // アニメーションの更新
        m_PlaybackTime = m_AnimationClipList[1]->Sample(m_CurrentPose, m_PlaybackTime + GraphicsMain::GetInstance()->deltaTime);
        m_PoseMatrix.clear();
        m_CurrentPose->GetMatrixPalette(m_PoseMatrix);

        Console::Log("m_PlaybackTime: %f / m_PoseMatrix.size(): %d / GraphicsMain::GetInstance()->deltaTime: %f\n", m_PlaybackTime, m_PoseMatrix.size(), GraphicsMain::GetInstance()->deltaTime);
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