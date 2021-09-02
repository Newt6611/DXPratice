#pragma once

#include <d3d11.h>
#include <string>

class SkyBox
{
public:
	SkyBox(std::string filePath);
	~SkyBox();



private:
	std::string m_FilePath;
	ID3D11ShaderResourceView* m_SRV;
};