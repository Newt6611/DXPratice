
cbuffer Pixel : register(b0)
{
	float alpha;
}

struct PS_IN {
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

SamplerState samplerState : SAMPLER : register(s0);

Texture2D texture0  : TEXTURE : register(t0);
Texture2D texture1  : TEXTURE : register(t1);
Texture2D texture2  : TEXTURE : register(t2);
Texture2D texture3  : TEXTURE : register(t3);
Texture2D texture4  : TEXTURE : register(t4);
Texture2D texture5  : TEXTURE : register(t5);
Texture2D texture6  : TEXTURE : register(t6);
Texture2D texture7  : TEXTURE : register(t7);
Texture2D texture8  : TEXTURE : register(t8);
Texture2D texture9  : TEXTURE : register(t9);
Texture2D texture10 : TEXTURE : register(t10);

float4 main(PS_IN ps_in) : SV_TARGET
{
	float4 t1 = texture0.Sample(samplerState, ps_in.texcoord);
	t1.a = alpha;
	return t1;
}