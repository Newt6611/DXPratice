#include "SamplerState.h"
#include "Renderer.h"
#include "Log.h"

SamplerState::SamplerState()
{
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MipLODBias = 0;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11Device* device = Renderer::Get()->GetDevice();
	HRESULT result = device->CreateSamplerState(&sampler_desc, &m_SamplerState);
	if (result != S_OK)
	{
		LogError("Failed When Creating SamplerState !");
	}
}

SamplerState::~SamplerState()
{
	m_SamplerState->Release();
}

void SamplerState::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->PSSetSamplers(0, 1, &m_SamplerState);
}