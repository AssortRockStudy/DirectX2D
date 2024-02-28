#ifndef _PARTICLE_UPDATE
#define _PARTICLE_UPDATE

#include "value.fx"
#include "struct.fx"

StructuredBuffer<FParticleModule>   g_ParticleModule : register(t20);
RWStructuredBuffer<FParticle>       g_ParticleBuffer : register(u0);
RWStructuredBuffer<FSpawnCount>     g_SpawnCount : register(u1);

#define MAX_COUNT   g_int_0
#define PARTICLE    g_ParticleBuffer[id.x]
#define SPAWN_COUNT g_SpawnCount[0].SpawnCount
#define MODULE      g_ParticleModule[0]

[numthreads(32, 1, 1)]
void CS_UpdateParticle(uint3 id : SV_DispatchThreadID)
{
    if (MAX_COUNT <= id.x)
        return;
    
    // case: Not Active Yet - Activation
    if (!PARTICLE.Active)
    {
        // -------------------------
        // Module : Spawn
        // -------------------------
        //if (MODULE.arrModuleCheck[0])
        //    return;
        
        while (SPAWN_COUNT > 0)
        {
            int AliveCount = SPAWN_COUNT;
            int Exchange = SPAWN_COUNT - 1;
            
            InterlockedCompareExchange(SPAWN_COUNT, AliveCount, Exchange, Exchange); // 스레드가 진입한 순서대로 돌아가지 않는 상황 고려해, 인자1이 예상한 값(인자2)과 같을 때만 함수 실행
            // InterlockedExchange(SPAWN_COUNT, Exchange, Exchange);    // 스레드가 진입한 순서대로 돌아가지 않을 수 있어 가끔 오류 발생
            if (Exchange == AliveCount)
            {
                PARTICLE.Active = 1;
                
                float fUV = (1.f / (MAX_COUNT - 1)) * id.x;
                float4 vColor = g_NoiseTex.SampleLevel(g_sam_0, float4(fUV, 0, 0, 0), 0.f);
                
                // spawn sahpe - sphere
                if (MODULE.SpawnShape == 0) 
                {
                    float RandomRadius = vColor.x * MODULE.Radius;
                    
                    // space 타입에 따라 생성방식 변함 (0: localspace, 1: worldspace)
                }
            }
        }
    }
    // case: Active
    else
    {
        PARTICLE.vWorldPos.y += g_dt * 100.f;
    }
}

#endif