#pragma once

#include <DirectXMath.h>

class Editor;

using namespace DirectX;

class Camera
{
public:
	Camera(float angle, float width, float height, float nearZ, float farZ);
	Camera(float width, float height, float nearZ, float farZ);
	~Camera();

	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }

	XMMATRIX GetView()const;
	XMMATRIX GetViewProjection() const;
	XMMATRIX GetProjection() const;
	XMFLOAT3 GetPosition() const;

	void SetWidthAndHeight(float width, float height);
private:
	void UpdateCamera();

private:
	bool isPerspective = true;
	XMVECTOR m_LookAt;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Up;
	XMFLOAT3 m_Right;

	float m_Angle;
	float m_Width;
	float m_Height;
	float m_NearZ;
	float m_FarZ;

	XMMATRIX m_View;
	XMMATRIX m_PersProjection;
	XMMATRIX m_OthoProjction;

	const XMVECTOR WORLD_UP = XMVectorSet(0, 1, 0, 1);
	const XMVECTOR WORLD_FORWARD = XMVectorSet(0, 0, 1, 1);

	friend class Editor;
};
