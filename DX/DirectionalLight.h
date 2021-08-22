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

	//void Bind(unsigned int slot);
	void SetDirection(XMFLOAT3 d);
	
	void Init();
	void Update();
	void Render(Camera* camera);

private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	Ref<ConstantBuffer<Directional_Light>> m_ConstantBuffer;
	XMFLOAT3 m_Ambient;
	XMFLOAT3 m_Diffuse;
	XMFLOAT3 m_Specular;

	friend class Editor;
};
