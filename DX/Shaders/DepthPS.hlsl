struct PS_IN
{
	float4 position : SV_POSITION;
	float4 depthPosition : TEXTURE0;
};

struct PS_OUT
{
	//float4 color : SV_TARGET;
	float depth : SV_DEPTH;
};

PS_OUT main(PS_IN ps_in)
{
	PS_OUT o;

	float depthValue;
	float4 color;
	
	depthValue = ps_in.position.z / ps_in.position.w;
	color = float4(depthValue, depthValue, depthValue, 1);

	//o.color = float4(depthValue, depthValue, depthValue, 1);
	o.depth = ps_in.position.z / ps_in.position.w;
	
	return o;
}