#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>



class Shader
{
public:
	Shader(LPCWSTR vertexFilePath, LPCWSTR pixelFilePath, int type);
	~Shader();

	inline ID3D11VertexShader* GetVertexShader() const { return m_VertexShader; }
	inline ID3D11PixelShader* GetPixelShader() const { return m_PixelShader; }
	inline ID3D11InputLayout* GetInputLayout() const { return m_InputLayout; }

	void Bind();

private:
	void CreateInputLayout(ID3DBlob* vs, int type);

private:
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;

	ID3D11InputLayout* m_InputLayout;

};