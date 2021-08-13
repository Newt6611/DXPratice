
struct VS_IN {
	float3 position : POSITION;
	float4 color : COLOR;
};

struct PS_IN {
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PS_IN main(VS_IN vs_in)
{
	PS_IN ps_in;

	ps_in.position = float4(vs_in.position, 1);
	ps_in.color = vs_in.color;

	return ps_in;
}