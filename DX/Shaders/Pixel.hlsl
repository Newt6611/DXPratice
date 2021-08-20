struct PS_IN {
	float4 position : SV_POSITION;
	float3 fragPos : FRAGPOS;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
	float3 normal : NORMAL;
};

struct DirectionalLight
{
	float4 color;
	float3 direction;

};


cbuffer PerFrame : register(b0)
{
	float alpha;
	float3 eyePos;
}


// for test
cbuffer DirectionalLight : register(b1)
{
	float4 Color;
	float3 Ambient;
	float3 Diffuse;
	float3 Specular;
	float3 Direction;
}


SamplerState samplerState  : SAMPLER : register(s0);

Texture2D diffuseTexture   : TEXTURE : register(t0);
Texture2D specularTexture  : TEXTURE : register(t1);
Texture2D normalTexture    : TEXTURE : register(t2);



float4 CaculateAmbient()
{
	float ambientStrenth = 0.1f;
	return ambientStrenth * Color;
}

float4 CaculateDiffuse(float3 normal, float2 texCoord)
{
	float diff = max(dot(normalize(Direction), normal), 0);
	return diff * diffuseTexture.Sample(samplerState, texCoord) * float4(Diffuse, 1);
}

float4 CaculateSpecular(float3 fragPos, float3 normal, float2 texCoord)
{
	float3 eyeDir = normalize(eyePos - fragPos);
	float3 refDir = reflect(normalize(Direction), normal);
	float spec = pow(max(dot(eyeDir, refDir), 0), 64);

	return spec * specularTexture.Sample(samplerState, texCoord) * Color;
}

float4 main(PS_IN ps_in) : SV_TARGET
{
	return CaculateAmbient() + CaculateDiffuse(ps_in.normal, ps_in.texcoord) + CaculateSpecular(ps_in.fragPos, ps_in.normal, ps_in.texcoord) * ps_in.color;
}