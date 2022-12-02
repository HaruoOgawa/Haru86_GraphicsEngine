#include "Time.h"

Time::Time(float fpsVal){
	fps = fpsVal;
	time = 0.0f;	
	m_DeltaTime = 1.0f / fps;
}

Time::~Time() {

}

void Time::UpdateTime() {
	time += m_DeltaTime;
}

float Time::GetTime() {
	return time;
}