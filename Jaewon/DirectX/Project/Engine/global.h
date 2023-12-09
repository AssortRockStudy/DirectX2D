#pragma once


#include <stdlib.h>
#include <Windows.h>

#include <wrl.h>
using namespace Microsoft::WRL;

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

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include "singleton.h"
#include "define.h"
#include "struct.h"