
struct VS_IN
{
	float3 position : POSITION;
};

struct PS_IN
{
	float4 position : SV_POSITION;
};

cbuffer PerObj : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
}

cbuffer LightViewPorjection : register(b1)
{
	matrix lightViewProjection;
}

PS_IN main(VS_IN vs_in) : SV_POSITION
{
	PS_IN ps_in;

	ps_in.position = mul(world, float4(vs_in.position, 1));
	ps_in.position = mul(lightViewProjection, ps_in.position);

	return ps_in;
}