
struct PS_IN {
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 main(PS_IN ps_in) : SV_TARGET
{
	return ps_in.color;
}