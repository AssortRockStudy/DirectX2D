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
            
            InterlockedCompareExchange(SPAWN_COUNT, AliveCount, Exchange, Exchange); // �����尡 ������ ������� ���ư��� �ʴ� ��Ȳ �����, ����1�� ������ ��(����2)�� ���� ���� �Լ� ����
            // InterlockedExchange(SPAWN_COUNT, Exchange, Exchange);    // �����尡 ������ ������� ���ư��� ���� �� �־� ���� ���� �߻�
            if (Exchange == AliveCount)
            {
                PARTICLE.Active = 1;
                
                float fUV = (1.f / (MAX_COUNT - 1)) * id.x;
                float4 vColor = g_NoiseTex.SampleLevel(g_sam_0, float4(fUV, 0, 0, 0), 0.f);
                
                // spawn sahpe - sphere
                if (MODULE.SpawnShape == 0) 
                {
                    float RandomRadius = vColor.x * MODULE.Radius;
                    
                    // space Ÿ�Կ� ���� ������� ���� (0: localspace, 1: worldspace)
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