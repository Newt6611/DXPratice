
cbuffer Pixel : register(b0)
{
	float alpha;
}

struct PS_IN {
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

SamplerState samplerState  : SAMPLER : register(s0);

Texture2D diffuseTexture   : TEXTURE : register(t0);
Texture2D specularTexture  : TEXTURE : register(t1);
Texture2D normalTexture    : TEXTURE : register(t2);



float4 main(PS_IN ps_in) : SV_TARGET
{
	float4 d = diffuseTexture.Sample(samplerState, ps_in.texcoord);
	float4 s = specularTexture.Sample(samplerState, ps_in.texcoord);
	float4 n = normalTexture.Sample(samplerState, ps_in.texcoord);
	float4 o = d;
	o.a = alpha;
	return o;
}