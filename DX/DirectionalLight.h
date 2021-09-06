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
	~DirectionalLight() {}

	void Bind();
	
	void SetDirection(XMFLOAT3 d);
	void SetAmbient(XMFLOAT3 color);
	void SetDiffuse(XMFLOAT3 color);
	void SetSpecular(XMFLOAT3 color);

	inline XMMATRIX GetLightViewProjection() const { return m_View * m_Projection; }
	Directional_Light GetLightData() const { return m_LightData; }
	
	void Init();
	void Update();
	void Render(Camera* camera);

private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	Directional_Light m_LightData;

	XMMATRIX m_Projection;
	XMMATRIX m_View;

	XMFLOAT3 m_Ambient;
	XMFLOAT3 m_Diffuse;
	XMFLOAT3 m_Specular;

	Ref<ConstantBuffer<VS_LightViewProjection>> m_ConstantBuffer;
	friend class Editor;
};
