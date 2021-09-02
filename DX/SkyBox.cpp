#include <codecvt>

#include "SkyBox.h"
#include "DDSTextureLoader.h"
#include "Renderer.h"

SkyBox::SkyBox(std::string filePath)
{
	std::wstring wFilePath = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filePath);
	HRESULT result = DirectX::CreateDDSTextureFromFile(Renderer::Get()->GetDevice(), wFilePath.c_str(), NULL, &m_SRV);
	if (result != S_OK)
	{
		LogError("Failed When Creating SkyBox !");
	}
}

SkyBox::~SkyBox()
{
}
