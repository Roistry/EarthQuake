#pragma once

class Vector2
{
public:
	float x, y;

	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void Print()
	{
		printf("x: %f, y: %f\n", this->x, this->y);
	}
};

class Vector3
{
public:
	float x, y, z;

	Vector3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	bool isValid()
	{
		if (this->x != 0 || this->y != 0 || this->z != 0)
			return true;
		return false;
	}
	float Distance(Vector3 other)
	{
		return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2) + pow(this->z - other.z, 2));
	}
	void Print()
	{
		printf("x: %f, y: %f, z: %f\n", this->x, this->y, this->z);
	}

	Vector3 operator+(Vector3 other)
	{
		Vector3 temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		temp.z = this->z + other.z;
		return temp;
	}
	Vector3 operator-(Vector3 other)
	{
		Vector3 temp;
		temp.x = this->x - other.x;
		temp.y = this->y - other.y;
		temp.z = this->z - other.z;
		return temp;
	}
	Vector3 operator*(Vector3 other)
	{
		Vector3 temp;
		temp.x = this->x * other.x;
		temp.y = this->y * other.y;
		temp.z = this->z * other.z;
		return temp;
	}
	Vector3 operator/(Vector3 other)
	{
		Vector3 temp;
		temp.x = this->x / other.x;
		temp.y = this->y / other.y;
		temp.z = this->z / other.z;
		return temp;
	}

	float DotProduct(Vector3 to)
	{
		return this->x * to.x + this->y * to.y + this->z * to.z;
	}

	//void operator+=(Vector3 other);
	//void operator-=(Vector3 other);
	//void operator*=(Vector3 other);
	//void operator/=(Vector3 other);
	//bool operator==(Vector3 other);
	//bool operator!=(Vector3 other);
};

class RGBA
{
public:
	float r, g, b, a;

	RGBA()
	{
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0;
	}
	RGBA(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	void ConvertToRGBA1();
	void ConvertToRGBA255();
	void Lerp(float value, float maxValue, RGBA endColor, RGBA startColor);
	void Print();

	RGBA operator+(RGBA other);
	RGBA operator-(RGBA other);
	RGBA operator*(RGBA other);
	RGBA operator/(RGBA other);

	void operator+=(RGBA other);
	void operator-=(RGBA other);
	void operator*=(RGBA other);
	void operator/=(RGBA other);
	bool operator==(RGBA other);
	bool operator!=(RGBA other);
};