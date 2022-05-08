#pragma once
#include <glm/glm.hpp>

namespace animation {
	template<typename T>
	class Bezier {
	public:
		T P1;
		T C1;
		T P2;
		T C2;
	};
	
	template<typename T>
	inline T Interpolate(Bezier<T>& curve,float t) {
		T A = glm::mix(curve.P1, curve.C1, t);
		T B = glm::mix(curve.C2, curve.P2, t);
		T C = glm::mix(curve.C1, curve.C2, t);

		T D = glm::mix(A, C, t);
		T E = glm::mix(C, B, t);

		T R = glm::mix(D, E, t);

		return R;
	}
}

