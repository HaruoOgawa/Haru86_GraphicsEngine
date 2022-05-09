#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "EInterpolationType.h"
#include "CFrame.h"

namespace animation {
	template<typename T,int N>
	class CTrack
	{
	public:
		CTrack(EInterpolationType InterpolationType);
		virtual ~CTrack();

		void Resize(unsigned int size);
		unsigned int GetSize()const;

		EInterpolationType GetInterpolationType()const;
		void SetInterpolationType(EInterpolationType InterpolationType);

		float GetStartTime()const;
		float GetEndTime()const;

		//
		T Sample(float time, bool looping);
		CFrame<N>& operator[](unsigned int index);
			
		//
		T Hermite(float t, const T& p1, const T& s1, const T& _p2, const T& s2);
	protected:
		// variable
		std::vector<CFrame<N>> m_Frames;
		EInterpolationType m_InterpolationType;

		// function
		T SampleConstant(float t, bool loop);
		T SampleLinear(float t, bool loop);
		T SampleCubic(float t, bool loop);

		int FrameIndex(float time, bool looping);
		float AdjustTimeToFitTrack(float time,bool loop);

		T Cast(float* value);
	};

	typedef CTrack<float, 1> ScalarTrack;
	typedef CTrack<glm::vec3, 3> VectorTrack;
	typedef CTrack<glm::quat, 4> QuaternionTrack;
}


