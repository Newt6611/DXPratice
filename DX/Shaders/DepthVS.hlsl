
struct VS_IN
{
	float3 position : POSITION;
};

struct PS_IN
{
	float4 position : SV_POSITION;
	float4 depthPosition : TEXTURE0;
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

PS_IN main(VS_IN vs_in)
{
	PS_IN ps_in;

	ps_in.position = mul(world, float4(vs_in.position, 1));
	ps_in.position = mul(view, ps_in.position);
	ps_in.position = mul(projection, ps_in.position);

	ps_in.depthPosition = ps_in.position;

	return ps_in;
}