#ifndef _FUNC
#define _FUNC

#include "struct.fx"
#include "value.fx"

void CalLight2D(float3 _WorldPos, int _LightIdx, inout tLightColor _output)
{
    tLightInfo info = g_Light2D[_LightIdx];
    
    if (0 == info.LightType)
    {
        _output.vAmbient += info.Color.vAmbient;
    }
    else if (1 == info.LightType)
    {
        float fAttenu = 1.f;
        float fDist = distance(info.vWorldPos.xy, _WorldPos.xy);
        
        if (fDist < info.fRadius)
        {
            if (g_int_0)
            {
                float fTheta = (fDist / info.fRadius) * (PI / 2.f);
                fAttenu = saturate(cos(fTheta));
            }
            else
            {
                fAttenu = saturate(1.f - fDist / g_Light2D[0].fRadius);
            }

            _output.vColor += info.Color.vColor * fAttenu;
        }
    }
    else if (2 == info.LightType)
    {
        float2 vecDir = _WorldPos.xy - info.vWorldPos.xy;
        float len = distance(_WorldPos.xy, info.vWorldPos.xy);
        
        if (len < info.fRadius)
        {
            if (acos(dot(vecDir, info.vWorldDir.xy) / len) <= info.fAngle)
            {
                _output.vColor += info.Color.vColor;
            }
        }

    }

}

#endif