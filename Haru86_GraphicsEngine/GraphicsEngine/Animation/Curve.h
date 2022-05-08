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
		return (
			curve.P1*((1.0f-t)*(1.0f-t)*(1.0f-t))+
			curve.C1*(3.0f*((1.0f-t) * (1.0f - t))*t)+
			curve.C2*(3.0f * (1.0f - t)*(t*t))+
			curve.P2*(t*t*t)
		);
	}
}

