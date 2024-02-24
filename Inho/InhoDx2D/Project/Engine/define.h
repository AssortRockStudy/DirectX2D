#pragma once

#define SINGLE(classtype) private:\
classtype();\
~classtype();\
friend class CSingleton<classtype>;

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State
#define DT	CTimeMgr::GetInst()->GetDeltaTime()

#define KEY_TAP(Key) KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, NONE)
#define LAYER_MAX 32

enum class DIR_TYPE {
	RIGHT,
	UP,
	FRONT
};

enum class ASSET_TYPE {
	MESH,
	MESHDATA,
	TEXTURE,
	MATERIAL,
	SOUND,
	COMPUTE_SHADER,
	GRAPHICS_SHADER,
	END,
};

enum class COMPONENT_TYPE {
	TRANSFORM,

	COLLIDER2D,
	COLLIDER3D,

	ANIMATOR2D,
	ANIMATOR3D,

	LIGHT2D,
	LIGHT3D,

	CAMERA,

	// render component
	MESHRENDER,
	TILEMAP,
	PARTICLESYSTEM,
	SKYBOX,
	DECAL,
	LANDSCAPE,

	END,

	SCRIPT,
};

enum class CB_TYPE {
	TRANSFORM,
	MATERIAL_CONST,
	ANIM2D_DATA,
	GLOBAL_DATA,
	ANIMATION,

	END,
};

enum class RS_TYPE {
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,
	END,
};

enum class DS_TYPE {
	LESS,
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL,
	NO_TEST,
	NO_WRITE,
	NO_TEST_NO_WRITE,
	END,
};

enum class BS_TYPE {
	DEFAULT,
	ALPHA_BLEND,
	ONE_ZERO,
	ONE_ONE,
	END,
};

// ScalarParam
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
	TEXARR_1,

	END,
};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,

	CUBE,
	SPHERE,
	CROSS,
};

enum class LIGHT_TYPE {
	DIRECTIONAL,
	POINT,
	SPOT,
};

enum class SHADER_DOMAIN {
	DOMAIN_OPAQUE,
	DOMAIN_MASKED,
	DOMAIN_TRANSPARENT,
	DOMAIN_POSTPROCESS,
	DOMAIN_DEBUG,
};

enum class PARTICLE_MODULE {
	SPAWN,
	DRAG,
	SCALE,
	INITIAL_VELOCITY,
	END,
};