struct VS_IN
{
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 bitangent : BITANGENT;
};

struct PS_IN
{
	float4 position : SV_POSITION;
	float3 fragPos : FRAGPOS;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
	float3x3 TBN : TBN;
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
	ps_in.color = color;

	float3 N = normalize(mul(world, vs_in.normal));
	float3 T = normalize(mul(world, vs_in.tangent));
	T = normalize(T - dot(T, N) * N);
	float3 B = normalize(cross(N, T));

	ps_in.TBN = float3x3(T, B, N);

	return ps_in;
}