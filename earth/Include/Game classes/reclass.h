#pragma once

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