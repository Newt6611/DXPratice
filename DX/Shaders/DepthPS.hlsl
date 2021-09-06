struct PS_IN
{
	float4 position : SV_POSITION;
};

float4 main(PS_IN ps_in) : SV_TARGET
{
	return float4(ps_in.position.z, ps_in.position.z, ps_in.position.z, 1);
}