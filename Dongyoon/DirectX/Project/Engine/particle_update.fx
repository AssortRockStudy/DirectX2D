#ifndef _PARTICLE_UPDATE
#define _PARTICLE_UPDATE

#include "value.fx"
#include "struct.fx"

StructuredBuffer<tParticleMoudle> g_Module : register(t20);
RWStructuredBuffer<tParticle> g_ParticleBuffer : register(u0);
RWStructuredBuffer<tSpawnCount>g_SpawnCount : register(u1);

#define MAX_COUNT   g_int_0
#define SpawnCount  g_SpawnCount[0].iSpawnCount
#define Particle    g_ParticleBuffer[id.x]

[numthreads(1024, 1, 1)]
void CS_ParticleUpdate(uint3 id : SV_DispatchThreadID)
{
    
    SpawnCount = 100;
    
    // 파티클이 비활성화 상태라면
    if (Particle.Active == 0)
    {
      if(0 < SpawnCount)
        {
            // Atomic 함수
            int AliveCount = SpawnCount;
            int Exchange = SpawnCount - 1;
            int Origin = 1;
            
            InterlockedExchange(SpawnCount, Exchange, Origin);
            
            if(AliveCount == Origin)
            {
                Particle.Active = 1;
            }
        }
    }
    else
    {
        Particle.vWorldPos.y += g_dt * 100.f;
    }
}

#endif