#ifndef _PARTICLE_UPDATE
#define _PARTICLE_UPDATE

#include "value.fx"
#include "struct.fx"

StructuredBuffer<tParticleModule> g_Module : register(t20);
RWStructuredBuffer<tParticle> g_ParticleBuffer : register(u0);
RWStructuredBuffer<tSpawnCount>g_SpawnCount: register(u1);

#define MAX_COUNT g_int_0
#define SpawnCount g_SpawnCount[0].iSpawnCount
#define Particle g_ParticleBuffer[id.x]
#define Module g_Module[0]

[numthreads(32, 1, 1)]
void CS_ParticleUpdate(uint3 id : SV_DispatchThreadID)
{
    if (MAX_COUNT <= id.x)
        return;
    

    if (0 == Particle.Active)
    {
        if (Module.arrModuleCheck[0])
            return;
        
        while (0 < SpawnCount)
        {
            int AliveCount = SpawnCount;
            int Exchange = SpawnCount - 1;
            int Origin = 0;
            
            InterlockedCompareExchange(SpawnCount, AliveCount, Exchange, Origin);
            
            if (AliveCount == Origin)
            {
                Particle.Active = 1;
                
                float2 vUV = float2((1.f / (MAX_COUNT - 1)) * id.x, 0.f);
                
                float4 vColor = g_NoiseTex.SampleLevel(g_sam_0, vUV, 0);
                
                if (0 == Module.SpawnModule.SpawnShape)
                {
                    float RandomRadius = vColor.x * Module.SpawnModule.Radius;
                    
                    Module.SpawnModule.SpaceType;
                }

                break;
            }
        }
    }
    else
    {
        Particle.vWorldPos.y += g_dt * 100.f;
    }

}

#endif
