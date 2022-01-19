#pragma once
#include <memory>

class Texture;
class CBloom;

class PostProcess
{
	bool m_UsePostProcess;
	bool m_UseBloom;
	float m_BloomIntensity;

	//bloom
	std::unique_ptr<CBloom> m_Bloom;
	std::shared_ptr<Texture> m_BloomTexture;
	unsigned int m_BloomFrameBuffer;
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
	void Initialize();
	void Release();
	void DrawBloom();
protected:
	static PostProcess* instance;
};

