#include "pch.h"
#include "CPathMgr.h"

wchar_t CPathMgr::g_szContent[255] = {};

void CPathMgr::init()
{
	GetCurrentDirectory(255, g_szContent);

	int Len = (int)wcslen(g_szContent);
	for (int i = Len - 1; i >= 0; --i)
	{
		if ('\\' == g_szContent[i])
		{
			g_szContent[i + 1] = '\0';
			break;
		}
	}

	wcscat_s(g_szContent, 255, L"Contents\\");
}
