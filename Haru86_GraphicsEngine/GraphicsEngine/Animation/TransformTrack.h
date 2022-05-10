#pragma once
#include "CTrack.h"

class TransformComponent;

namespace animation {
	class TransformTrack
	{
	protected:
		unsigned int mId;
		VectorTrack m_Position;
		QuaternionTrack m_Rotation;
		VectorTrack m_Scale;
	public:
		TransformTrack();
		~TransformTrack() = default;

		unsigned int GetID()const;
		void SetId(unsigned int id);

		VectorTrack& GetPositionTrack();
		QuaternionTrack& GetRotationTrack();
		VectorTrack& GetScaleTrack();

		float GetStartTime();
		float GetEndTime();

		bool IsValid();

		TransformComponent Sample(const TransformComponent& ref, float time, bool looping);
	};
}