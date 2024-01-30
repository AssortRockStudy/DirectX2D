#ifndef _PARTICLE_UPDATE
#define _PARTICLE_UPDATE

#include "value.fx"
#include "struct.fx"

StructuredBuffer<tParticleModule>   g_Module : register(t31);
RWStructuredBuffer<tParticle>       g_ParticleBuffer : register(u0);
RWStructuredBuffer<tSpawnCount>     g_SpawnCount : register(u1);

#define MAX_COUNT   g_int_0
#define SpawnCount  g_SpawnCount[0].iSpawnCount
#define Particle    g_ParticleBuffer[id.x]
#define Module      g_Module[0]
#define CenterPos   g_vec4_0.xyz

[numthreads(32, 1, 1)]
void CS_ParticleUpdate(uint3 id :SV_DispatchThreadID)
{
    if (MAX_COUNT <= id.x)
        return;
    
    if(0 == Particle.Active)
    {
        // 스폰 모듈 활성화 체크
        if (0 == Module.arrModuleCheck[0])
            return;
        
        while (0 < SpawnCount)
        {
            int AliveCount = SpawnCount;
            uint Origin = 0;
        
            // InterlockedExchange 함수를 써서 SpawnCount를 교체, 수정하면
            // 초기 시도인 스레드가 여러 스레드 성공 이후에 진입하는 경우가 있음
            // 이때 SpawnCount를 오히려 늘려버리는 현상이 발생할 수 있으므로
            // InterlockedCompareExchange 함수를 통해서 예상한 값과 일치할 경우에만
            // 교체를 하도록 하는 함수를 사용한다
            InterlockedCompareExchange(SpawnCount, AliveCount, SpawnCount - 1, Origin);
        
            if (AliveCount == Origin)
            {
                Particle.Active = 1;
                
                // 랜덤
                float2 vUV = float2((1.f / (MAX_COUNT - 1)) * id.x, 0.f);
                
                vUV.x += g_time * 0.2f;
                //                  ( 주파수)     (진폭)   (y축 오프셋)
                vUV.y = sin(vUV.x * 20.f * PI) * 0.2f + g_time * 0.1f;
                
                float4 vRand = g_NoiseTex.SampleLevel(g_sam_0, vUV, 0);
                
                // SpawnShape가 Sphere일 경우
                if(0 == Module.SpawnShape)
                {
                    float RandomRadius = vRand[0] * Module.Radius;
                    float RandomAngle = vRand[1] * 2 * PI;
                    
                    // Particle 컴포넌트의 중심위치에서
                    // 랜덤 각도, 랜덤 반지름에 해당하는 위치를 계산해서 파티클 초기 위치로 조정
                    Particle.vLocalPos.xyz = float3(cos(RandomAngle), sin(RandomAngle), 0.f) * RandomRadius;
                }
                else
                {
                    Particle.vLocalPos.x = vRand[0] * Module.vSpawnBoxScale.x - (Module.vSpawnBoxScale.x / 2.f);
                    Particle.vLocalPos.y = vRand[1] * Module.vSpawnBoxScale.y - (Module.vSpawnBoxScale.y / 2.f);
                    Particle.vLocalPos.z = 0.f;
                }
                
                // 위에서 조정한 로컬 좌표를 가져와 월드 좌표로 재설정
                Particle.vWorldPos.xyz = Particle.vLocalPos.xyz + CenterPos;
        
                // 스폰 컬러 설정
                Particle.vColor = Module.vSpawnColor;
                
                // 스폰 크기 설정
                Particle.vWorldScale = (Module.vSpawnMaxScale - Module.vSpawnMinScale) * vRand[2] + Module.vSpawnMinScale;
                
                // 스폰 Life 설정
                Particle.Age = 0.f;
                Particle.Life = (Module.MaxLife - Module.MinLife) * vRand[0] + Module.MaxLife;
                
                // Add Velocity
                if (Module.arrModuleCheck[3])
                {
                    // From Center
                    if (0 == Module.AddVelocityType)
                    {
                        float3 vDir = normalize(Particle.vLocalPos.xyz);
                        Particle.vVelocity.xyz = vDir * clamp(vRand[2], Module.MinSpeed, Module.MaxSpeed);
                    }
                    // To Center
                    else if (1 == Module.AddVelocityType)
                    {
                        float3 vDir = -normalize(Particle.vLocalPos.xyz);
                        Particle.vVelocity.xyz = vDir * clamp(vRand[2], Module.MinSpeed, Module.MaxSpeed);
                    }
                }
                
                break;
            }
        }
    }
    else
    {
        Particle.Age += g_dt;
        
        if (Particle.Life < Particle.Age)
        {
            Particle.Active = 0;
            return;
        }
        
        if (0 == Module.SpaceType)
        {
            Particle.vLocalPos.xyz += Particle.vVelocity.xyz * g_dt;
            Particle.vWorldPos.xyz = Particle.vLocalPos.xyz + CenterPos;
        }
        else if (1 == Module.SpaceType)
        {
            Particle.vWorldPos.xyz += Particle.vVelocity.xyz * g_dt;
        }
    }
}


#endif