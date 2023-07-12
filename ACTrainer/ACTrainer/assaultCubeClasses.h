#pragma once
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
	int8_t playerDirectionY; //0x0080
	int8_t playerDirectionX; //0x0081
	char pad_0082[10]; //0x0082
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
	char pad_0184[120]; //0x0184
	int32_t playerScore; //0x01FC
	char pad_0200[37]; //0x0200
	char PlayerName[16]; //0x0225
	char pad_0235[247]; //0x0235
	int32_t currentTeam; //0x032C
	char pad_0330[24]; //0x0330
	void* weaponlistptr; //0x0348
	char pad_034C[40]; //0x034C
	class WeaponClass* currWeaponPtr; //0x0374
	char pad_0378[28]; //0x0378
}; //Size: 0x0394

class WeaponClass
{
public:
	int32_t wepId; //0x0004
	class PlayerObj* Owner; //0x0008
	class WeaponDataStructures* weaponData; //0x000C
	int32_t* ReservedAmmo; //0x0010
	int32_t* MagAmmo; //0x0014
	void* gunWaitTime; //0x0018
	int32_t conSequtiveShots; //0x001C
	int32_t Reloading; //0x0020
	char pad_0024[12]; //0x0024

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
}; //Size: 0x0030

class WeaponDataStructures
{
public:
	char weaponName[28]; //0x0000
	char pad_001C[232]; //0x001C
	int16_t N000007BD; //0x0104
	int16_t N00000894; //0x0106
	int16_t N000007BE; //0x0108
	int16_t N00000899; //0x010A
	int16_t baseWepDmg; //0x010C
	int16_t N0000089C; //0x010E
	int16_t N000007C0; //0x0110
	int16_t N000008A2; //0x0112
	int16_t N000007C1; //0x0114
	int16_t N000008A4; //0x0116
	int16_t N000007C2; //0x0118
	int16_t N000008A6; //0x011A
	int16_t N000007C3; //0x011C
	int16_t N000008A8; //0x011E
	int16_t N000007C4; //0x0120
	int16_t N000008AA; //0x0122
	int16_t N000007C5; //0x0124
	int16_t N000008AC; //0x0126
	int16_t N000007C6; //0x0128
}; //Size: 0x012A

class entityList
{
public:
	char pad_0000[4]; //0x0000
	class PlayerObj* entityArr[32]; //0x0004
}; //Size: 0x0084

class entityInfo
{
public:
	char pad_0000[4]; //0x0000
	class PlayerObj* localPlayerObjPtr; //0x0004
	class entityList* entityListPtr; //0x0008
	int32_t numOfEntities; //0x000C
	char pad_0010[4]; //0x0010
}; //Size: 0x0014