#include "Camera.h"
#include "Log.h"
#include "Input.h"
#include "Timer.h"

Camera::Camera(float angle, float width, float height, float nearZ, float farZ)
	: m_Angle(angle), m_Width(width), m_Height(height), m_NearZ(nearZ), m_FarZ(farZ),
	m_Position(0, 0, -15), m_Rotation(0, 0, 0)
{
	m_PersProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(angle), static_cast<float>(width) / static_cast<float>(height), nearZ, farZ);
	m_OthoProjction = XMMatrixOrthographicLH(static_cast<float>(width), static_cast<float>(height), nearZ, farZ);

	m_View = XMMatrixIdentity();
	UpdateCamera();
}

Camera::Camera(float width, float height, float nearZ, float farZ)
	: m_Angle(45), m_Width(width), m_Height(height), m_NearZ(nearZ), m_FarZ(farZ),
	m_Position(0, 5, -15), m_Rotation(XMConvertToRadians(20), 0, 0)
{
	m_PersProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45), static_cast<float>(width) / static_cast<float>(height), nearZ, farZ);
	m_OthoProjction = XMMatrixOrthographicLH(static_cast<float>(width), static_cast<float>(height), nearZ, farZ);

	m_View = XMMatrixIdentity();
	UpdateCamera();
}

Camera::~Camera()
{

}

void Camera::Update()
{
	if (Input::IsKeyDown(SDL_SCANCODE_W))
	{
		m_Position.z += 15 * Timer::DeltaTime;
	}
	else if (Input::IsKeyDown(SDL_SCANCODE_S))
	{
		m_Position.z -= 15 * Timer::DeltaTime;
	}

	if (Input::IsKeyDown(SDL_SCANCODE_D))
	{
		m_Position.x += 15 * Timer::DeltaTime;
	}
	else if (Input::IsKeyDown(SDL_SCANCODE_A))
	{
		m_Position.x -= 15 * Timer::DeltaTime;
	}


	UpdateCamera();
}

XMMATRIX Camera::GetView() const
{
	return m_View;
}

XMMATRIX Camera::GetViewProjection() const
{
	if (isPerspective)
		return XMMatrixMultiply(m_View, m_PersProjection);
	else
		return XMMatrixMultiply(m_View, m_OthoProjction);
}

XMMATRIX Camera::GetProjection() const
{
	if (isPerspective)
		return m_PersProjection;
	else
		return m_OthoProjction;
}

XMFLOAT3 Camera::GetPosition() const
{
	return m_Position;
}

void Camera::SetWidthAndHeight(float width, float height)
{
	if (height == m_Height && width == m_Width)
		return;
	m_Width = width;
	m_Height = height;
	m_PersProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(m_Angle), static_cast<float>(width) / static_cast<float>(height), m_NearZ, m_FarZ);
	m_OthoProjction = XMMatrixOrthographicLH(static_cast<float>(width), static_cast<float>(height), m_NearZ, m_FarZ);
	
	UpdateCamera();
}

void Camera::UpdateCamera()
{
	XMMATRIX rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	XMVECTOR look_vec = XMVector3Transform(WORLD_FORWARD, rot);

	m_LookAt = XMVectorSet( m_Position.x, m_Position.y, m_Position.z, 1 ) + look_vec;

	XMVECTOR up = XMVector3TransformCoord(WORLD_UP, rot);
	m_View = XMMatrixLookAtLH(XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 1), m_LookAt, up);
}
