#ifndef _PARTICLE_UPDATE
#define _PARTICLE_UPDATE

#include "value.fx"
#include "struct.fx"

RWStructuredBuffer<FParticle> g_ParticleBuffer : register(u0);

#define MAX_CONT g_int_0

[numthreads(1024, 1, 1)]
void CS_UpdateParticle(uint3 id : SV_DispatchThreadID)
{
	g_ParticleBuffer[id.x].vWorldPos.y = id.x * 0.5f;
}

#endif