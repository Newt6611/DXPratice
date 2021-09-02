#pragma once

#include "Base.h"
#include "ConstantBuffer.h"
#include "IGameObject.h"

class World;
class Editor;

class DirectionalLight : public IGameObject
{
public:
	DirectionalLight(World* world, ID3D11Device* device, ID3D11DeviceContext* context);
	DirectionalLight(World* world, XMFLOAT3 color, XMFLOAT3 direction, ID3D11Device* device, ID3D11DeviceContext* context);
	~DirectionalLight() {}

	void SetDirection(XMFLOAT3 d);
	void SetAmbient(XMFLOAT3 color);
	void SetDiffuse(XMFLOAT3 color);
	void SetSpecular(XMFLOAT3 color);


	Directional_Light GetLightData() const { return m_LightData; }
	
	void Init();
	void Update();
	void Render(Camera* camera);

private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	Directional_Light m_LightData;

	XMFLOAT3 m_Ambient;
	XMFLOAT3 m_Diffuse;
	XMFLOAT3 m_Specular;

	friend class Editor;
};
