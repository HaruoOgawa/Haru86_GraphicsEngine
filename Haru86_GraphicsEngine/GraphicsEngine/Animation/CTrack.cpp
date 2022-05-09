#include "CTrack.h"
#include "CFrame.h"
#include <glm/gtc/quaternion.hpp>

namespace animation {
	template CTrack<float, 1>;
	template CTrack<glm::vec3, 3>;
	template CTrack<glm::quat, 4>;

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