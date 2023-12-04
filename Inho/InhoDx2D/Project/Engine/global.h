#pragma once

#include <stdlib.h>
#include <Windows.h>

// 스마트 포인터 사용하기 위함
#include <wrl.h>
using namespace Microsoft::WRL;

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include "singleton.h"
#include "define.h"
#include "struct.h"
