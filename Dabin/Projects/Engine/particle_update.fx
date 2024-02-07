#ifndef _PARTICLE_UPDATE
#define _PARTICLE_UPDATE

#include "value.fx"
#include "struct.fx"

StructuredBuffer<FParticleModule> g_ParticleModule : register(t20);
RWStructuredBuffer<FParticle> g_ParticleBuffer : register(u0);
RWStructuredBuffer<FSpawnCount> g_SpawnCount : register(u1);

#define PARTICLE g_ParticleBuffer[id.x]
#define SPAWN_COUNT g_SpawnCount[0].SpawnCount

[numthreads(1024, 1, 1)]
void CS_UpdateParticle(uint3 id : SV_DispatchThreadID)
{
    // case: Not Active Yet - Activation
    if (!PARTICLE.Active)
    {
        if (SPAWN_COUNT > 0)
        {
            int AliveCount = SPAWN_COUNT;
            int Exchange = SPAWN_COUNT - 1;
            
            InterlockedCompareExchange(SPAWN_COUNT, AliveCount, Exchange, Exchange);
            // InterlockedExchange(SPAWN_COUNT, Exchange, Exchange);
            if (Exchange == AliveCount)
                PARTICLE.Active = 1;
        }
    }
    // case: Active
    else
    {
        PARTICLE.vWorldPos.y += g_dt * 100.f;
    }
}

#endif