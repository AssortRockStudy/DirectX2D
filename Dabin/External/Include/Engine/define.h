#pragma once

#define SINGLE(classType)	private:\
								classType();\
								~classType();\
							friend class CSingleton<classType>;

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define DT	CTimeMgr::GetInst()->GetDeltaTime()

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::State
#define KEY_TAP(Key) KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, NONE)

#define LAYER_MAX 32

enum class ASSET_TYPE
{
	MESH,
	MESHDATA,
	TEXTURE,
	MATERIAL,
	SOUND,
	COMPUTE_SHADER,
	GRAPHICS_SHADER,

	END,
};

enum class COMPONENT_TYPE
{
	TRANSFORM,	// ������Ʈ�� ��ġ,ũ��,ȸ��
	COLLIDER2D,	// 2���� �浹ü
	COLLIDER3D, // 3���� �浹ü
	ANIMATOR2D,	// ��������Ʈ Animation
	ANIMATOR3D,	// Bone Skinning Animation
	LIGHT2D,	// 2���� ����
	LIGHT3D,	// 3���� ����
	CAMERA,		// ī�޶� ���

	// Render Component
	MESHRENDER,
	TILEMAP,
	PARTICLESYSTEM,
	SKYBOX,
	DECAL,
	LANDSCAPE,

	END,
	// Before End: basic type
	// -------------------------------
	// After End: custom type (added by user)

	SCRIPT,
};

// type of constant buffer
enum class CB_TYPE
{
	TRANSFORM,
	MATREIAL_CONST,
	GLOBAL_DATA,
	ANIMTATION,

	END,
};

// type of direction vector
enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT
};