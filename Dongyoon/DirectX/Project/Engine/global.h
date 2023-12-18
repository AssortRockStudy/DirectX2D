#pragma once

//표준 라이브러리
#include <stdlib.h>
#include <Windows.h>
#include <typeinfo>

#include <wrl.h>
using namespace Microsoft::WRL;

#include <string>

using std::wstring;
using std::string;

#include <vector>
#include <list>
#include <map>

using std::vector;
using std::list;
using std::map;
using std::make_pair;

// Directx 11 헤더 및 라이브러리 참조
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

using namespace DirectX;

//Simple Math
#include "SimpleMath.h"
using namespace DirectX::SimpleMath;

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

//엔진 헤더 참조
#include "CSingleton.h"
#include "define.h"
#include "struct.h"
#include "func.h"