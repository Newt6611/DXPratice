#pragma once

#include <d3d11.h>
#include <string>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>

enum TextureType
{
	Diffuse,
	Specular,
	Normal
};

class Texture 
{
public:
	Texture(std::string filePath);
	Texture(std::string filePath, TextureType type);
	~Texture();

	inline std::string GetPath() const { return m_FilePath; }
	inline TextureType GetType() const { return m_Type; }

	void Bind(unsigned int slot);
	inline ID3D11ShaderResourceView* GetTexture() const { return m_Texture; }

private:
	void CreateTexture();

private:
	TextureType m_Type;
	std::string m_FilePath;
	std::wstring m_WFilePath;
	ID3D11ShaderResourceView* m_Texture;
};