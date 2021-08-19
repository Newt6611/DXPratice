#pragma once
#include <vector>
#include "Renderer.h"
class World;

class IGameObject
{
public:
	virtual void Init() = 0;
	virtual void Update()
	{
		m_World = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z) *
			XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z) *
			XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	}
	virtual void Render() = 0;

	void SetPosition(XMFLOAT3 p)
	{
		m_Position = p;
	}

	void SetRotation(XMFLOAT3 r)
	{
		m_Rotation = r;
	}

	void SetScale(XMFLOAT3 s)
	{
		m_Scale = s;
	}

	inline XMFLOAT3 GetPosition() const { return m_Position; }
	inline XMFLOAT3 GetRotation() const { return m_Rotation; }
	inline XMFLOAT3 GetScale() const { return m_Scale; }

protected:
	XMMATRIX m_World;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
};