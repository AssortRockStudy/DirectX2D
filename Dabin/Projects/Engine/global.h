#pragma once

// Windows header
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <list>
#include <map>
using std::wstring;
using std::string;
using std::vector;
using std::list;
using std::map;
using std::make_pair;

#include <wrl.h>
using namespace Microsoft::WRL;

// C runtime header
#include <stdlib.h>

// Dirext 11
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
using namespace DirectX;

// SimpleMath
#include "SimpleMath.h"
using namespace DirectX::SimpleMath;
typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

// Engine
#include "singleton.h"
#include "define.h"
#include "struct.h"