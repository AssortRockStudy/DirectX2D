#ifndef _FUNC
#define _FUNC

#include "struct.fx"
#include "value.fx"

void CalLight2D(float3 _vWorldPos, int _LightIdx, inout tLightColor _output)
{
    tLightInfo info = g_Light2D[_LightIdx];
    
    // Directional Light
    if (info.LightType == 0)
        _output.vAmbient += info.Color.vAmbient;
    
    // Point Light
    else if (info.LightType == 1)
    {
        float fAttenue = 1.f;
        float fDist = distance(info.vWorldPos.xy, _vWorldPos.xy);
        
        if (fDist < info.fRadius)
        {
            float fTheta = (fDist / info.fRadius) * (PI / 2.f); // 0~1사이 값을 0~pi/2로 매칭시킴
            fAttenue = saturate(cos(fTheta));
            
            _output.vColor += info.Color.vColor * fAttenue;
        }
    }
    
    // Spot Light
    else if (info.LightType == 2)
    {
        float fDist = distance(info.vWorldPos.xy, _vWorldPos.xy);
        
        if (fDist < info.fRadius)
        {
            // 1. 광원과 현재 픽셀, 두 점 사이의 각(float) 구함
            // - 아크탄젠트를 사용해서 구할 수도 있고 (정확한 값, 연산 부담)
            // - 백터의 내적을 사용해서 구할 수도 있음 (벡터 사이각 체크, 연산 쉬움)
            float2 pixelVec = (_vWorldPos.xy - info.vWorldPos.xy);
            float fVecScale = (sqrt(pow(info.vWorldDir.x, 2) + pow(info.vWorldDir.y, 2))) * (sqrt(pow(pixelVec.x, 2) + pow(pixelVec.y, 2))); // 두 vector의 크기 구함
            float fDot = (pixelVec.x * info.vWorldDir.x) + (pixelVec.y * info.vWorldDir.y); // 내적값 구함 (2D: z는 0+0으로 두고 xy만 계산)
            float fAngle = acos(fDot / fVecScale); // θ 구함
            
            if (fAngle <= info.fAngle / 2.f)
            {
                float fAttenu = 1.f;
                float fTheta = (fDist / info.fRadius) * (PI / 2.f);
                fAttenu = saturate(cos(fTheta));
                _output.vColor += info.Color.vColor * fAttenu;
            }
        }
    }
}

#endif