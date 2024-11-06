#pragma once

class Vector3D
{
public:
	Vector3D():m_x(0), m_y(0), m_z(0)
	{
		
	}

	Vector3D(float x, float y, float z) :m_x(x), m_y(y), m_z(z)
	{

	}

	Vector3D(const Vector3D& vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
	{

	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta) {
		Vector3D v;
		v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
		v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
		v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);

		return v;
	}
	
	Vector3D operator *(float num) {
		return Vector3D(m_x * num, m_y * num, m_z * num);
	}

	Vector3D operator +(Vector3D vec) {
		return Vector3D(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	Vector3D operator -(Vector3D vec) {
		return Vector3D(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
	}

	Vector3D Cross(const Vector3D& other) const {
		return Vector3D(
			m_y * other.m_z - m_z * other.m_y,  // X component
			m_z * other.m_x - m_x * other.m_z,  // Y component
			m_x * other.m_y - m_y * other.m_x   // Z component
		);
	}

	// Rotate around the X axis
	void RotateX(float angle) {
		float rad = angle * (3.14159265f / 180.0f); // Convert degrees to radians
		float cosAngle = cos(rad);
		float sinAngle = sin(rad);

		float newY = m_y * cosAngle - m_z * sinAngle;
		float newZ = m_y * sinAngle + m_z * cosAngle;

		m_y = newY;
		m_z = newZ;
	}

	// Rotate around the Y axis
	void RotateY(float angle) {
		float rad = angle * (3.14159265f / 180.0f); // Convert degrees to radians
		float cosAngle = cos(rad);
		float sinAngle = sin(rad);

		float newX = m_x * cosAngle + m_z * sinAngle;
		float newZ = -m_x * sinAngle + m_z * cosAngle;

		m_x = newX;
		m_z = newZ;
	}

	void Normalize() {
		float length = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
		if (length > 0) {
			m_x /= length;
			m_y /= length;
			m_z /= length;
		}
	}

	static Vector3D Zeros() {
		Vector3D zeroVec;
		zeroVec.m_x = 0;
		zeroVec.m_y = 0;
		zeroVec.m_z = 0;

		return zeroVec;
	}

	static Vector3D Ones() {
		Vector3D zeroVec;
		zeroVec.m_x = 1;
		zeroVec.m_y = 1;
		zeroVec.m_z = 1;

		return zeroVec;
	}

	static Vector3D up() { 
		return Vector3D(0, 1, 0); 
	}

	~Vector3D()
	{
	}

	float m_x, m_y, m_z;
};