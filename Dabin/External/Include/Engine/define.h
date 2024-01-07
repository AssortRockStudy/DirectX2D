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

// Direction Vector
enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT
};

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
	TRANSFORM,	// 오브젝트의 위치,크기,회전
	COLLIDER2D,	// 2차원 충돌체
	COLLIDER3D, // 3차원 충돌체
	ANIMATOR2D,	// 스프라이트 Animation
	ANIMATOR3D,	// Bone Skinning Animation
	LIGHT2D,	// 2차원 광원
	LIGHT3D,	// 3차원 광원
	CAMERA,		// 카메라 기능

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

// Constant Buffer Type
enum class CB_TYPE
{
	TRANSFORM,
	MATREIAL_CONST,
	GLOBAL_DATA,
	ANIMTATION,

	END,
};

// Rasterizer State Type
enum class RS_TYPE
{
	CULL_BACK,	// CCW(Counter Clock Wise) - default
	CULL_FRONT,	// CW
	CULL_NONE,
	WIRE_FRAME,	// outline

	END,
};

// DepthStencil State Type
enum class DS_TYPE
{
	LESS,				// 더 가까우면 통과			, 깊이 기록 O
	LESS_EQUAL,			// 더 가깝거나 같으면 통과	, 깊이 기록 O

	GREATER,			// 더 멀면 통과				, 깊이 기록 O
	GREATER_EQAUL,		// 더 멀거나 같으면 통과	, 깊이 기록 O

	NO_TEST,			// 깊이 테스트 X			, 깊이 기록 O
	NO_WRITE,			// 깊이 테스트 O			, 깊이 기록 X
	NO_TEST_NO_WRITE,	// 깊이 테스트 X			, 깊이 기록 X

	END,
};

// Blend State Type
enum class BS_TYPE
{
	DEFAULT,
	ALPHA_BLEND,
	ONE_ONE,

	END,
};
