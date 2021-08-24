struct VS_IN 
{
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
	float3 normal : NORMAL;
};

struct PS_IN 
{
	float4 position : SV_POSITION;
	float3 fragPos : FRAGPOS;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
	float3 normal : NORMAL;
};

cbuffer PerObj : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
	float4 color;
}

PS_IN main(VS_IN vs_in)
{
	PS_IN ps_in;

	ps_in.position = mul(world, float4(vs_in.position, 1));
	ps_in.position = mul(view, ps_in.position);
	ps_in.position = mul(projection, ps_in.position);
	
	ps_in.fragPos = mul(world, float4(vs_in.position, 1));
	ps_in.texcoord = vs_in.texcoord;
	ps_in.normal = normalize(mul(world, vs_in.normal));
	ps_in.color = color;

	return ps_in;
}