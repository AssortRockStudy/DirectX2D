#pragma once

#include <stdlib.h>
#include <Windows.h>
#include <typeinfo>
#include <string>

#include <vector>
#include <list>
#include <map>

using std::vector;
using std::list;
using std::map;
using std::make_pair;

using std::wstring;
using std::string;

// 스마트 포인터 사용하기 위함
#include <wrl.h>
using namespace Microsoft::WRL;

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <DirectXTex/DirectXTex.h>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex")
#endif

// SimpleMath
#include "SimpleMath.h"
using namespace DirectX::SimpleMath;

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

#include "singleton.h"
#include "define.h"
#include "struct.h"
#include "func.h"
