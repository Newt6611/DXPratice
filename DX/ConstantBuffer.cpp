//#include "ConstantBuffer.h"
//#include "Renderer.h"
//#include "Log.h"
//#include "Shader.h"
//
//template<typename T>
//ConstantBuffer<T>::ConstantBuffer(ShaderStage stage)
//	: m_ShaderStage(stage)
//{
//	ID3D11Device* device = Renderer::Get()->GetDevice();
//
//	D3D11_BUFFER_DESC buffer_desc;
//	buffer_desc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
//	buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
//	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	buffer_desc.MiscFlags = 0;
//	buffer_desc.StructureByteStride = 0;
//
//	HRESULT result = device->CreateBuffer(&buffer_desc, nullptr, &m_Buffer);
//	if (result != S_OK)
//	{
//		LogError("Failed When Creating Constant Buffer !");
//	}
//}
//
//template<typename T>
//ConstantBuffer<T>::~ConstantBuffer()
//{
//}
//
//template<typename T>
//void ConstantBuffer<T>::Bind(unsigned int slot)
//{
//	ID3D11DeviceContext* context = Renderer::Get()->GetContext();
//
//	D3D11_MAPPED_SUBRESOURCE map_data;
//	ZeroMemory(&map_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
//
//	context->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_Data);
//
//	CopyMemory(map_data.pData, &m_Data, sizeof(T));
//	context->Unmap(m_Buffer, 0);
//
//	switch (m_ShaderStage)
//	{
//	case VS:
//		context->VSSetConstantBuffers(slot, 1, &m_Buffer);
//		break;
//	case PS:
//		context->PSSetConstantBuffers(slot, 1, &m_Buffer);
//		break;
//	}
//}
//
//template<typename T>
//void ConstantBuffer<T>::SetData(T data)
//{
//	this->m_Data = data;
//}
