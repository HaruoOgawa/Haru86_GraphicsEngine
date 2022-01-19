#pragma once
#include <memory>

class Texture;

class PostProcess
{
	bool m_UsePostProcess;
	bool m_UseBloom;
	float m_BloomIntensity;
public:
	static void CreateInstance();
	static PostProcess* GetInstance();
	static void DestroyInstance();
	
	PostProcess();
	~PostProcess();
	void EnablePostProcess();
	const bool GetUsePostProcess()const;
	void DrawPolygonPostProcess(const std::shared_ptr<Texture> SrcTexture,const unsigned int& DestBuffer)const;
	void DrawLatePostProcess(const std::shared_ptr<Texture> SrcTexture, const unsigned int& DestBuffer)const;
	void EnableBloom(float bloomIntensity);
	
private:
	//void DrawBloom()
protected:
	static PostProcess* instance;
};

