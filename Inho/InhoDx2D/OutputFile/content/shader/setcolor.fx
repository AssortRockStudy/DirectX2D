#ifndef _SETCOLOR
#define _SETCOLOR

#include "value.fx"

#define TEX_WIDTH g_int_0
#define TEX_HEIGHT g_int_1
RWTexture2D<float4> g_TargetTex : register(u0);

[numthreads(32, 32, 1)]
void CS_SetColor(uint3 id: SV_DispatchThreadID)
{
    if(TEX_WIDTH <= id.x || TEX_HEIGHT <= id.y)
        return;
    
    if (500 <= id.y && id.y <= 600)
        g_TargetTex[id.xy] = float4(g_vec4_0.rgb, 1.f);

}

#endif