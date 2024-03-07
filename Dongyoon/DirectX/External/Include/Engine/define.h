#pragma once

#define SINGLE(classtype)	private:\
								classtype();\
								~classtype();\
							friend class CSingleton<classtype>;

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State
#define DT	CTimeMgr::GetInst()->GetDeltaTime()
#define DTd CTimeMgr::GetInst()->GetDeltaTime_d()

#define KEY_TAP(Key) KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, NONE)


#define LAYER_MAX 32

enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT,
};

enum class ASSET_TYPE
{
	MESH,
	MESHDATA,
	TEXTURE,
	MATERIAL,
	SOUND,
	COMPUTE_SHADER,
	GRAPHIC_SHADER,
	END
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

	SCRIPT,
};

// 상수버퍼 종류
enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL_CONST,
	ANIM2D_DATA,
	GLOBAL_DATA,
	ANIMATION,

	END,
};

//Rasterizer State Type
enum class RS_TYPE
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,

	END,
};


//DepthStencil State Type
enum class DS_TYPE
{
	LESS,					//작은게 통과				깊이 기록 O
	LESS_EQUAL,				//작거나 같으면통과			깊이 기록 0

	GRATER,					//더 멀면 통과				깊이 기록 0
	GRATER_EQUAL,			//더 멀거나 같으면 통과		깊이 기록 0

	NO_TEST,				//깊이 테스트 X				깊이 기록 0
	NO_WRITE,				//깊이 테스트 0				깊이 기록 X

	NO_TEST_NO_WRITE,		//깊이 테스트 X				깊이 기록 X

	END,
};


//Blend State
enum class BS_TYPE
{
	DEFAULT,

	ALPHA_BLEND,

	ONE_ZERO,

	ONE_ONE,

	END,
};



// Scalar Param
enum SCALAR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,
	MAT_1,
	MAT_2,
	MAT_3,
};

enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEXCUBE_0,
	TEXCUBE_1,

	TEXARR_0,
	TEXCARR_1,

	END,

};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	CROSS,

	CUBE,
	SPHERE,
};

enum class LIGHT_TYPE
{
	DIRECTIONAL,
	POINT,
	SPOT,
};

enum class SHADER_DOMAIN
{
	DOMAIN_OPAQUE,		//불투명
	DOMAIN_MASKED,		//불투명 OR 투명
	DOMAIN_TRANSPARENT,	//반투명
	DOMAIN_POSTPROCESS, //후처리

	DOMAIN_DEBUG,
};

enum class PARTICLE_MODULE
{
	SPAWN,// 파티클 생성 관련
	DRAG,// 감속 관련 모듈
	SCALE,// 크기 변화 모듈
	ADD_VELOCITY,// 초기 속도 지정 모듈
	NOISE_FORCE,
	CALCULATE_FORCE, // 주어진 힘을 계산하는 모듈

	Render, // 렌더링 때의 옵션 관련

	END,
};