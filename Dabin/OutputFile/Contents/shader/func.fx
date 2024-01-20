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
            float fTheta = (fDist / info.fRadius) * (PI / 2.f); // 0~1���� ���� 0~pi/2�� ��Ī��Ŵ
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
            // 1. ������ ���� �ȼ�, �� �� ������ ��(float) ����
            // - ��ũź��Ʈ�� ����ؼ� ���� ���� �ְ� (��Ȯ�� ��, ���� �δ�)
            // - ������ ������ ����ؼ� ���� ���� ���� (���� ���̰� üũ, ���� ����)
            float2 pixelVec = (_vWorldPos.xy - info.vWorldPos.xy);
            float fVecScale = (sqrt(pow(info.vWorldDir.x, 2) + pow(info.vWorldDir.y, 2))) * (sqrt(pow(pixelVec.x, 2) + pow(pixelVec.y, 2))); // �� vector�� ũ�� ����
            float fDot = (pixelVec.x * info.vWorldDir.x) + (pixelVec.y * info.vWorldDir.y); // ������ ���� (2D: z�� 0+0���� �ΰ� xy�� ���)
            float fAngle = acos(fDot / fVecScale); // �� ����
            
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