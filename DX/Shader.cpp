#include "Shader.h"
#include "Renderer.h"

Shader::Shader(LPCWSTR vertexFilePath, LPCWSTR pixelFilePath, int type = 0)
{
	ID3D11Device* device = Renderer::Get()->GetDevice();
	ID3DBlob* vblob = nullptr;
	ID3DBlob* pblob = nullptr;
	ID3DBlob* error = nullptr;
	HRESULT result;

	result = D3DCompileFromFile(vertexFilePath, NULL, NULL, "main", "vs_5_0", 0, 0, &vblob, &error);
	result = D3DCompileFromFile(pixelFilePath, NULL, NULL, "main", "ps_5_0", 0, 0, &pblob, &error);

	if (result != S_OK)
	{
		LogError("Failed When Compiling Shaders !");
		LogError(error->GetBufferPointer());
	}

	result = device->CreateVertexShader(vblob->GetBufferPointer(), vblob->GetBufferSize(), NULL, &m_VertexShader);
	result = device->CreatePixelShader(pblob->GetBufferPointer(), pblob->GetBufferSize(), NULL, &m_PixelShader);

	if (result != S_OK)
	{
		LogError("Failed When Creating Shaders !");
	}

	CreateInputLayout(vblob, type);

	vblob->Release();
	pblob->Release();
	if(error != nullptr)
		error->Release();
}

Shader::~Shader()
{
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_InputLayout->Release();
}

void Shader::Bind()
{
	ID3D11DeviceContext* context = Renderer::Get()->GetContext();

	context->IASetInputLayout(m_InputLayout);
	context->VSSetShader(m_VertexShader, 0, 0);
	context->PSSetShader(m_PixelShader, 0, 0);
}

void Shader::CreateInputLayout(ID3DBlob* vs, int type)
{
	ID3D11Device* device = Renderer::Get()->GetDevice();

	if (type == 1)
	{
		D3D11_INPUT_ELEMENT_DESC input_desc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		HRESULT result = device->CreateInputLayout(input_desc, 3, vs->GetBufferPointer(), vs->GetBufferSize(), &m_InputLayout);
		if (result != S_OK)
		{
			LogError("Failed When Createing InputLayout !");
		}
	}

	else if (type == 2)
	{
		D3D11_INPUT_ELEMENT_DESC input_desc[] = {
			{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BITANGENT",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		HRESULT result = device->CreateInputLayout(input_desc, 5, vs->GetBufferPointer(), vs->GetBufferSize(), &m_InputLayout);
		if (result != S_OK)
		{
			LogError("Failed When Createing InputLayout !");
		}
	}
}
