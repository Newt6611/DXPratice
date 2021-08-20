cbuffer PerObj : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
	float3 color;
}


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
	float3 color : COLOR;
	float2 texcoord : TEXCOORD;
	float3 normal : NORMAL;
};

PS_IN main(VS_IN vs_in)
{
	PS_IN ps_in;

	ps_in.position = mul(float4(vs_in.position, 1), world);
	ps_in.position = mul(ps_in.position, view);
	ps_in.position = mul(ps_in.position, projection);
	
	ps_in.fragPos = mul(float4(vs_in.position, 1), world);
	ps_in.color = color;
	ps_in.texcoord = vs_in.texcoord;
	ps_in.normal = normalize(mul(vs_in.normal, world));

	return ps_in;
}