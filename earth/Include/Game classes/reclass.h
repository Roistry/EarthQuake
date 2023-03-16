#pragma once

#define	CONTENTS_SOLID			1		// an eye is never valid in a solid
#define	CONTENTS_LAVA			8
#define	CONTENTS_SLIME			16
#define	CONTENTS_WATER			32
#define	CONTENTS_FOG			64

#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000
//bot specific contents types
#define	CONTENTS_TELEPORTER		0x40000
#define	CONTENTS_JUMPPAD		0x80000
#define CONTENTS_CLUSTERPORTAL	0x100000
#define CONTENTS_DONOTENTER		0x200000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_BODY			0x2000000	// should never be on a brush, only in game
#define	CONTENTS_CORPSE			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes not used for the bsp
#define	CONTENTS_STRUCTURAL		0x10000000	// brushes used for the bsp
#define	CONTENTS_TRANSLUCENT	0x20000000	// don't consume surface fragments inside
#define	CONTENTS_TRIGGER		0x40000000
#define	CONTENTS_NODROP			0x80000000	// don't leave bodies or items (death fog, lava)

#define	SURF_NODAMAGE			0x1		// never give falling damage
#define	SURF_SLICK				0x2		// effects game physics
#define	SURF_SKY				0x4		// lighting from environment map
#define	SURF_LADDER				0x8
#define	SURF_NOIMPACT			0x10	// don't make missile explosions
#define	SURF_NOMARKS			0x20	// don't leave missile marks
#define	SURF_FLESH				0x40	// make flesh sounds and effects
#define	SURF_NODRAW				0x80	// don't generate a drawsurface at all
#define	SURF_HINT				0x100	// make a primary bsp splitter
#define	SURF_SKIP				0x200	// completely ignore, allowing non-closed brushes
#define	SURF_NOLIGHTMAP			0x400	// surface doesn't need a lightmap
#define	SURF_POINTLIGHT			0x800	// generate lighting info at vertexes
#define	SURF_METALSTEPS			0x1000	// clanking footsteps
#define	SURF_NOSTEPS			0x2000	// no footstep sounds
#define	SURF_NONSOLID			0x4000	// don't collide against curves with this set
#define SURF_LIGHTFILTER		0x8000	// act as a light filter during q3map -light
#define	SURF_ALPHASHADOW		0x10000	// do per-pixel light shadow casting in q3map
#define	SURF_NODLIGHT			0x20000	// never add dynamic lights

// content masks
#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_BODY)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE)

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

class refdef_t
{
public:
	int            x, y, width, height;
	float          fov_x, fov_y;
	Vector3        vieworg;
	Vector3        viewaxis[3];

	Vector2 WorldToScreen(Vector3 src, Vector3 dst)
	{
		Vector3 transform;
		float xc, yc;
		float px, py;
		float z;

		px = tan(this->fov_x * 3.141f / 360.0);
		py = tan(this->fov_y * 3.141f / 360.0);

		transform = dst - src;

		xc = this->width / 2.0;
		yc = this->height / 2.0;

		z = transform.DotProduct(this->viewaxis[0]);

		Vector2 screenCords;
		if (z <= 0.1)
			return screenCords;

		screenCords.x = xc - transform.DotProduct(this->viewaxis[1]) * xc / (z * px);
		screenCords.y = yc - transform.DotProduct(this->viewaxis[2]) * yc / (z * py);

		return screenCords;
	}
};

struct trace_t
{
	void* brush;
	void* face;
	void* terraface;
	float dist;
	bool selected;
};