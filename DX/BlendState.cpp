#include "BlendState.h"
#include "Renderer.h"

BlendState::BlendState()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();

	// None
	D3D11_RENDER_TARGET_BLEND_DESC render_target_blend;
	ZeroMemory(&render_target_blend, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));
	render_target_blend.BlendEnable = false;
	render_target_blend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	render_target_blend.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	render_target_blend.BlendOp = D3D11_BLEND_OP_ADD;
	render_target_blend.SrcBlendAlpha = D3D11_BLEND_ONE;
	render_target_blend.DestBlendAlpha = D3D11_BLEND_ZERO;
	render_target_blend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	render_target_blend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	D3D11_BLEND_DESC blend_desc;
	ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));
	blend_desc.AlphaToCoverageEnable = false;
	blend_desc.IndependentBlendEnable = false;
	blend_desc.RenderTarget[0] = render_target_blend;

	HRESULT result = device->CreateBlendState(&blend_desc, &m_NoneBlendState);
	if (result != S_OK)
	{
		LogError("Failed When Creating NoneBlendState !");
	}

	// Transparency
	render_target_blend.BlendEnable = true;
	blend_desc.AlphaToCoverageEnable = false;
	blend_desc.RenderTarget[0] = render_target_blend;
	result = device->CreateBlendState(&blend_desc, &m_TransparencyState);
	if (result != S_OK)
	{
		LogError("Failed When Creating TransparencyBlendState !");
	}


	SetBlendState(BlendStateType::Transparency);
}

BlendState::~BlendState()
{
	m_TransparencyState->Release();
	m_NoneBlendState->Release();
}

BlendState* BlendState::SetBlendState(BlendStateType type)
{
	if (m_CurrentType == type)
		return this;

	switch (type)
	{
	case None:
		m_CurrentBlendState = m_NoneBlendState;
		m_CurrentType = type;
		break;
	case Transparency:
		m_CurrentBlendState = m_TransparencyState;
		m_CurrentType = type;
		break;
	}

	return this;
}

void BlendState::Bind()
{
	float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->OMSetBlendState(m_CurrentBlendState, blendFactor, 0xFFFFFFFF);
}
