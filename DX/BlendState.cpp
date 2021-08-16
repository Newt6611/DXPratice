#include "BlendState.h"
#include "Renderer.h"


BlendState::BlendState()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();

	D3D11_RENDER_TARGET_BLEND_DESC render_target_blend;
	render_target_blend.BlendEnable = true;
	render_target_blend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	render_target_blend.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	render_target_blend.BlendOp = D3D11_BLEND_OP_ADD;
	render_target_blend.SrcBlendAlpha = D3D11_BLEND_ONE;
	render_target_blend.DestBlendAlpha = D3D11_BLEND_ZERO;
	render_target_blend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	render_target_blend.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;


	D3D11_BLEND_DESC blend_desc;
	blend_desc.AlphaToCoverageEnable = true;
	blend_desc.IndependentBlendEnable = false;
	blend_desc.RenderTarget[0] = render_target_blend;

	HRESULT result = device->CreateBlendState(&blend_desc, &m_BlendState);
	if (result != S_OK)
	{
		LogError("Failed When Creating Blend State !");
	}


}

BlendState::~BlendState()
{
	m_BlendState->Release();
}

void BlendState::Bind()
{
	float blendFactor[] = { 1.f, 0, 0, 1.0f };
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->OMSetBlendState(m_BlendState, blendFactor, 0xFFFFFFFF);
}
