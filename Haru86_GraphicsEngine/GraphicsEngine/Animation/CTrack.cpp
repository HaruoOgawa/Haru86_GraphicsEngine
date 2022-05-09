#include "CTrack.h"
#include "CFrame.h"
#include <glm/gtc/quaternion.hpp>

namespace animation {
	template CTrack<float, 1>;
	template CTrack<glm::vec3, 3>;
	template CTrack<glm::quat, 4>;

	template<typename T,int N>
	CTrack<T,N>::CTrack(EInterpolationType InterpolationType) :
		m_InterpolationType(InterpolationType)
	{
	}

	template<typename T,int N>
	CTrack<T, N>::~CTrack() {
		m_Frames.clear();
	}

	template<typename T, int N>
	float CTrack<T, N>::GetStartTime()const {
		return m_Frames[0].m_Time;
	}

	template<typename T, int N>
	float CTrack<T, N>::GetEndTime()const {
		return m_Frames[m_Frames.size() - 1].m_Time;
	}

	//
	template<typename T,int N>
	T CTrack<T,N>::Sample(float time, bool looping) {
		if (m_InterpolationType==EInterpolationType::Constant) {
			return SampleConstant(time, looping);
		}
		else if (m_InterpolationType==EInterpolationType::Linear) {
			return SampleLinear(time, looping);
		}
		else if(m_InterpolationType==EInterpolationType::Cubic) {
			return SampleCubic(time, looping);
		}
	}

	template<typename T,int N>
	CFrame<N>& CTrack<T, N>::operator[](unsigned int index) {
		return m_Frames[index];
	}

	//
	template<typename T, int N>
	T CTrack<T, N>::Hermite(float t, const T& p1, const T& s1, const T& _p2, const T& s2) {
		float tt = t * t;
		float ttt = tt * t;

		T p2 = _p2;
		TrackHelpers::Neighborhood(p1, p2);

		float h1 = 2.0f * ttt - 3.0f * tt + 1.0f;
		float h2 = -2.0f * ttt + 3.0f * tt;
		float h3 = ttt - 2.0f * tt + t;
		float h4 = ttt - tt;

		T result = p1 * h1 + p2 * h2 + s1 * h3 + s2 * h4;
		return TrackHelpers::AdjustHermiteResult(result);
	}

	template<typename T,int N>
	void CTrack<T, N>::Resize(unsigned int size) {
		m_Frames.resize(size);
	}

	template<typename T,int N>
	unsigned int CTrack<T, N>::GetSize()const {
		return m_Frames.size();
	}

	template<typename T, int N>
	EInterpolationType CTrack<T, N>::GetInterpolationType()const {
		return m_InterpolationType;
	}
	
	template<typename T, int N>
	void CTrack<T, N>::SetInterpolationType(EInterpolationType InterpolationType) {
		m_InterpolationType = InterpolationType;
	}

	namespace TrackHelpers {
		inline float Interpolate(float a, float b, float t) {
			return a + (b - a) * t;
		}

		inline glm::vec3 Interpolate(const glm::vec3& a, const glm::vec3& b, float t) {
			return glm::mix(a, b, t);
		}

		inline glm::quat Interpolate(const glm::quat& a, const glm::quat& b, float t) {
			glm::quat result = glm::mix(a, b, t);
			if (glm::dot(a, b) < 0) {
				result = glm::mix(a, -b, t);
			}
			return glm::normalize(result);
		}

		inline float AdjustHermiteResult(float f) {
			return f;
		}

		inline glm::vec3 AdjustHermiteResult(const glm::vec3& v) {
			return v;
		}

		inline glm::quat AdjustHermiteResult(const glm::quat& q) {
			return glm::normalize(q);
		}

		inline void Neighborhood(const float& a,float& b){}
		inline void Neighborhood(const glm::vec3& a, glm::vec3& b){}

		inline void Neighborhood(const glm::quat& a, glm::quat& b){
			if (glm::dot(a, b) < 0) {
				b = -b;
			}
		}
	}
}