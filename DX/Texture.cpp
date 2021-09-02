#include <codecvt>


#include "Texture.h"
#include "Renderer.h"
#include "Log.h"

Texture::Texture(std::string filePath)
	: m_FilePath(filePath), m_Type(TextureType::Diffuse)
{
	m_WFilePath = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filePath);
	CreateTexture();
}

Texture::Texture(std::string filePath, TextureType type)
	: m_FilePath(filePath), m_Type(type)
{
	m_WFilePath = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filePath);
	CreateTexture();
}



Texture::~Texture()
{
	if(m_Texture != nullptr)
		m_Texture->Release();
}

void Texture::Bind(unsigned int slot)
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	if (m_Texture == nullptr)
		LogError("NULL");
	else
		context->PSSetShaderResources(slot, 1, &m_Texture);
}

void Texture::CreateTexture()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	HRESULT result = DirectX::CreateWICTextureFromFile(device, context, m_WFilePath.c_str(), nullptr, &m_Texture);
	if (result != S_OK)
	{
		LogError("Failed When Creating Texture ! ");
		LogError(m_FilePath);
	}
}
