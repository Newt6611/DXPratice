#pragma once

#include "ConstantBuffer.h"
#include "IGameObject.h"

class World;
class Editor;

class PointLight : public IGameObject
{
public:
	PointLight(World* world, ID3D11Device* device, ID3D11DeviceContext* context);
	~PointLight();

	void Init();
	void Update();
	void Render(Camera* camera);

	Point_Light GetLightData() const { return m_LightData; }

private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	Point_Light m_LightData;

	XMFLOAT3 m_Ambient = XMFLOAT3(1, 1, 1);
	XMFLOAT3 m_Diffuse = XMFLOAT3(1, 1, 1);
	XMFLOAT3 m_Specular = XMFLOAT3(1, 1, 1);
	
	float m_Constant = 1;
	float m_Linear = 0.14;
	float m_Quadratic = 0.07;

	friend class Editor;
};