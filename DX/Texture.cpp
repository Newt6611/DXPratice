#include "Texture.h"
#include "Renderer.h"
#include "Log.h"

Texture::Texture(std::wstring filePath)
	: m_FilePath(filePath)
{
	ID3D11Device* device = Renderer::Get()->GetDevice();
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	HRESULT result = DirectX::CreateWICTextureFromFile(device, context, filePath.c_str(), nullptr, &m_Texture);
	if (result != S_OK)
	{
		LogError("Failed When Creating Texture ! ");
	}
}

Texture::~Texture()
{
	delete m_Texture;
}

void Texture::Bind(unsigned int slot)
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	
	context->PSSetShaderResources(slot, 1, &m_Texture);
}
