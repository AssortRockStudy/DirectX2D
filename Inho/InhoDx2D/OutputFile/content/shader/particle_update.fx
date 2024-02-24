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
#define CenterPos g_vec4_0.xyz

[numthreads(32, 1, 1)]
void CS_ParticleUpdate(uint3 id : SV_DispatchThreadID)
{
    if (MAX_COUNT <= id.x)
        return;
    

    if (0 == Particle.Active)
    {
        if (0 == Module.arrModuleCheck[0])
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
                
                vUV.x += g_time * 0.2f;
                vUV.y = sin(vUV.x * 20.f * PI) * 0.2f + g_time * 0.1f;
                
                float4 vRand = g_NoiseTex.SampleLevel(g_sam_0, vUV, 0);
                
                if (0 == Module.SpawnModule.SpawnShape)
                {
                    float RandomRadius = vRand[0].x * Module.SpawnModule.Radius;
                    float RandomAngle = vRand[1] * 2 * PI;
                    
                    Particle.vLocalPos.xyz = float3(cos(RandomAngle), sin(RandomAngle), 0) * RandomRadius;
                }
                else
                {
                    Particle.vLocalPos.x = vRand[0] * Module.SpawnModule.vSpawnBoxScale.x - (Module.SpawnModule.vSpawnBoxScale.x / 2.f);
                    Particle.vLocalPos.y = vRand[1] * Module.SpawnModule.vSpawnBoxScale.y - (Module.SpawnModule.vSpawnBoxScale.y / 2.f);
                    Particle.vLocalPos.z = 0.f;
                }
                
                Particle.vWorldPos.wyz = Particle.vLocalPos.xyz + CenterPos;
                
                Particle.vColor = Module.SpawnModule.vSpawnColor;
                
                Particle.Age = 0.f;
                Particle.Life = (Module.SpawnModule.MaxLife - Module.SpawnModule.MinLife) * vRand[0] + Module.SpawnModule.MaxLife;
                
                if (Module.arrModuleCheck[3])
                {
                    if (0 == Module.VeloctiyModule.AddVelocityType)
                    {
                        float3 vDir = normalize(Particle.vLocalPos.xyz);
                        Particle.vVelocity.xyz = vDir * clamp(vRand[2], Module.VeloctiyModule.MinSpeed, Module.VeloctiyModule.MaxSpeed);
                    }
                    else if(1 == Module.VeloctiyModule.AddVelocityType)
                    {
                        float3 vDir = -normalize(Particle.vLocalPos.xyz);
                        Particle.vVelocity.xyz = vDir * clamp(vRand[2], Module.VeloctiyModule.MinSpeed, Module.VeloctiyModule.MaxSpeed);
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

        if (0 == Module.SpawnModule.SpaceType)
        {
            Particle.vLocalPos.xyz += Particle.vVelocity.xyz * g_dt;
            Particle.vWorldPos.xyz = Particle.vLocalPos.xyz + CenterPos;
        }
        else if (1 == Module.SpawnModule.SpaceType)
        {
            Particle.vWorldPos.xyz += Particle.vVelocity.xyz * g_dt;
        }

    }

}

#endif
