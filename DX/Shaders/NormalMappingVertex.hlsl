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

	ps_in.position = mul(float4(vs_in.position, 1), world);
	ps_in.position = mul(ps_in.position, view);
	ps_in.position = mul(ps_in.position, projection);

	ps_in.fragPos = mul(float4(vs_in.position, 1), world);
	ps_in.texcoord = vs_in.texcoord;
	ps_in.color = color;

	float3 N = normalize(mul(vs_in.normal, world));
	float3 T = normalize(mul(vs_in.tangent, world));
	T = normalize(T - dot(T, N) * N);
	float3 B = cross(T, N);

	ps_in.TBN = float3x3(N, B, T);

	return ps_in;
}