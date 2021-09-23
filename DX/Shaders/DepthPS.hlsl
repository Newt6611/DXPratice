struct PS_IN
{
	float4 position : SV_POSITION;
	float4 depthPosition : TEXTURE0;
};

float4 main(PS_IN ps_in) : SV_TARGET
{
	float depthValue;
	float4 color;

	depthValue = ps_in.position.z / ps_in.position.w;
	color = float4(depthValue, depthValue, depthValue, 1);


	return color;
}