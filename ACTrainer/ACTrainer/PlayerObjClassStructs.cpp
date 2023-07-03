// Created with ReClass.NET 1.2 by KN4CK3R
#include <stdio.h>
#include <stdint.h>

class Vector3
{
public:
	float x;
	float y;
	float z;
};

class PlayerObj
{
public:
	void* vTable; //0x0000
	Vector3 headPos; //0x0004
	char pad_0010[36]; //0x0010
	Vector3 PlayerPos; //0x0034
	Vector3 PlayerAngles; //0x0040
	char pad_004C[52]; //0x004C
	int32_t playerDirection; //0x0080
	char pad_0084[8]; //0x0084
	int32_t playerVelocity; //0x008C
	char pad_0090[104]; //0x0090
	int32_t PlayerHP; //0x00F8
	int32_t Armor; //0x00FC
	char pad_0100[20]; //0x0100
	int32_t AmmoResPistol; //0x0114
	char pad_0118[16]; //0x0118
	int32_t AmmoResAR; //0x0128
	char pad_012C[16]; //0x012C
	int32_t AmmoPistol; //0x013C
	char pad_0140[16]; //0x0140
	int32_t ammoAssaultRifle; //0x0150
	char pad_0154[4]; //0x0154
	int32_t numGrenades; //0x0158
	char pad_015C[4]; //0x015C
	int32_t KnifeWaitTime; //0x0160
	int32_t PistolWaittime; //0x0164
	char pad_0168[16]; //0x0168
	int32_t AssaultRifleWaitTime; //0x0178
	char pad_017C[4]; //0x017C
	int32_t grenadeWaitTime; //0x0180
	char pad_0184[161]; //0x0184
	char PlayerName[16]; //0x0225
	char pad_0235[319]; //0x0235
	class WeaponClass* currWeapon; //0x0374
	char pad_0378[364]; //0x0378
}; //Size: 0x04E4

class WeaponClass
{
public:
	int32_t wepId; //0x0004
	class N00000328* Owner; //0x0008
	char* wepName; //0x000C
	class N0000035E* Ammo; //0x0010
	class N000001FC* MagAmmo; //0x0014
	void* gunWaitTime; //0x0018
	int32_t conSequtiveShots; //0x001C
	int32_t Reloading; //0x0020
	char pad_0024[32]; //0x0024

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0044

class N00000302
{
public:
	char pad_0000[4]; //0x0000
}; //Size: 0x0004

class N00000328
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044

class N0000035E
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044

class N00000395
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044

class N000001FC
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044