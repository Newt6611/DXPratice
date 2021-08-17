#include "RasterzierState.h"
#include "Renderer.h"
#include "Display.h"

RasterzierState::RasterzierState()
{
	ID3D11Device* device = Renderer::Get()->GetDevice();
	HRESULT result;

	// Create Solid State
	D3D11_RASTERIZER_DESC rasterizer_desc;
	ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_BACK;
	rasterizer_desc.FrontCounterClockwise = false;
	rasterizer_desc.DepthClipEnable = true;
	result = device->CreateRasterizerState(&rasterizer_desc, &m_SolidState);
	if (result != S_OK)
		MessageBox(Display::Get()->GetHandle(), L"Failed Creating Solid State", L"Error", ERROR);

	// Create Wireframe State
	rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;
	result = device->CreateRasterizerState(&rasterizer_desc, &m_WireFrameState);
	if (result != S_OK)
		MessageBox(Display::Get()->GetHandle(), L"Failed Creating WireFrame State", L"Error", ERROR);

	SetState(RasterzierStateType::Solid);
}

RasterzierState::~RasterzierState()
{
	delete m_SolidState;
	delete m_WireFrameState;
}

void RasterzierState::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
	context->RSSetState(m_CurrentState);
}

RasterzierState* RasterzierState::SetState(RasterzierStateType type)
{
	if (m_CurrentType == type)
		return this;

	switch (type)
	{
	case Solid:
		m_CurrentType = type;
		m_CurrentState = m_SolidState;
		break;
	case WireFrame:
		m_CurrentType = type;
		m_CurrentState = m_WireFrameState;
		break;
	}
	
	return this;
}
