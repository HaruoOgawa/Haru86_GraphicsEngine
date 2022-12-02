#pragma once
class Time
{
public:
	Time(float fpsVal);
	~Time();
	void UpdateTime();
	float GetTime();
	float fps;
	float m_DeltaTime;
	friend class UIComponent;
private:
	float time;
};

