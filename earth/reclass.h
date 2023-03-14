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

class Entity
{
public:
	char pad_0000[20]; //0x0000
	Vector3 pos; //0x0014
	Vector3 velocity; //0x0020
	char pad_002C[61]; //0x002C
	bool shooting; //0x0069
	char pad_006A[54]; //0x006A
	Vector3 viewangles; //0x00A0
	char pad_00AC[20]; //0x00AC
	int32_t health; //0x00C0
	char pad_00C4[12]; //0x00C4
	int32_t shield; //0x00D0
	char pad_00D4[180]; //0x00D4
	int32_t iYellowAmmo; //0x0188
	int32_t iOrangeAmmo; //0x018C
	int32_t iGreenAmmo; //0x0190
	int32_t iRedAmmo; //0x0194
	int32_t iWhiteAmmo; //0x0198
	int32_t iLightGreenAmmo; //0x019C
	int32_t iPurpleAmmo; //0x01A0
	char pad_01A4[20]; //0x01A4
	int32_t iDarkYellowAmmo; //0x01B8
	char pad_01BC[2588]; //0x01BC
}; //Size: 0x0BD8

class EntityList
{
public:
	class Entity aEntities[32]; //0x0000
	char pad_4A060[5264]; //0x4A060
}; //Size: 0x4B4F0