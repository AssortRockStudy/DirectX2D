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
	GLOBAL_DATA,
	ANIMATION,

	END,
};