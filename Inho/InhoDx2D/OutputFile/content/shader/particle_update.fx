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
                float4 vRand1 = g_NoiseTex.SampleLevel(g_sam_0, vUV - float2(0.1f, 0.1f), 0);
                float4 vRand2 = g_NoiseTex.SampleLevel(g_sam_0, vUV - float2(0.2f, 0.2f), 0);
                
                
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
                
                Particle.vWorldInitScale = Particle.vWorldScale = (Module.SpawnModule.vSpawnMaxScale - Module.SpawnModule.vSpawnMinScale) * vRand[2] + Module.SpawnModule.vSpawnMinScale;
                
                Particle.Age = 0.f;
                Particle.Life = (Module.SpawnModule.MaxLife - Module.SpawnModule.MinLife) * vRand[0] + Module.SpawnModule.MaxLife;
                
                Particle.Mass = clamp(vRand1[0], Module.SpawnModule.MinMass, Module.SpawnModule.MaxMass);
                
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
                else
                {
                    Particle.vVelocity.xyz = float3(0.f, 0.f, 0.f);

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

        // 랜덤값 추출
        float2 vUV = float2((1.f / (MAX_COUNT - 1)) * id.x, 0.f);
        vUV.x += g_time * 0.2f;
        vUV.y = sin(vUV.x * 20.f * PI) * 0.2f + g_time * 0.1f;
        float4 vRand = g_NoiseTex.SampleLevel(g_sam_0, vUV, 0);
        
        Particle.vForce.xyz = float3(0.f, 0.f, 0.f);
        
        // Normalize Age 계산
        Particle.NormalizedAge= Particle.Age / Particle.Life;
        
        // Scale 모듈
        if (Module.arrModuleCheck[2])
        {
            Particle.vWorldScale = Particle.vWorldInitScale * (1.f + (Module.ScaleModule.vScaleRatio - 1.f) * Particle.NormalizedAge);
        }
        
        // Noise Force
        if (Module.arrModuleCheck[4])
        {
            float3 vRandomForce = normalize(vRand.xyz - 0.5f);
            Particle.vForce.xyz += Module.NoiseForce.NoiseForceScale * vRandomForce;
        }
        
        
        // Calculate Force
        if (Module.arrModuleCheck[5])
        {
            // Force 연산
            // F = M x A
            float3 vAccel = Particle.vForce.xyz / Particle.Mass;
            
            // Accel 연산
            Particle.vVelocity.xyz += vAccel * g_dt;
            
            // Velocity 연산
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
}

#endif
