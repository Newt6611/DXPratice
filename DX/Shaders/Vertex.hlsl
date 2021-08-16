cbuffer PerObj : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
}


struct VS_IN {
	float3 position : POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

struct PS_IN {
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

PS_IN main(VS_IN vs_in)
{
	PS_IN ps_in;


	ps_in.position = mul(float4(vs_in.position, 1), world);
	ps_in.position = mul(ps_in.position, view);
	ps_in.position = mul(ps_in.position, projection);
	
	ps_in.color = vs_in.color;
	ps_in.texcoord = vs_in.texcoord;


	return ps_in;
}