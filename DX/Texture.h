#pragma once

#include <d3d11.h>
#include <string>
#include <WICTextureLoader.h>

class Texture 
{
public:
	Texture(std::string filePath);
	~Texture();

	inline ID3D11ShaderResourceView* GetTexture() const { return m_Texture; }

private:
	std::string m_FilePath;
	ID3D11ShaderResourceView* m_Texture;
};