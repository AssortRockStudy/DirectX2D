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

[numthreads(1024, 1, 1)]
void CS_ParticleUpdate(uint3 id :SV_DispatchThreadID)
{
    if(0 == Particle.Active)
    {
        if (0 < SpawnCount)
        {
            uint Origin = 0;
        
            InterlockedExchange(SpawnCount, SpawnCount - 1, Origin);
        
            if (0 < Origin)
            {
                Particle.Active = 1;
            }
        }
    }
    else
    {
        Particle.vWorldPos.y += g_dt * 10.f;
        //Particle.vWorldPos.y = 100.f;

    }
}


#endif