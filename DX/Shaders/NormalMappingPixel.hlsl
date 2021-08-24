struct PS_IN {
	float4 position : SV_POSITION;
	float3 fragPos : FRAGPOS;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
	float3 normal : NORMAL;
	float3x3 TBN : TBN;
};

struct DirectionalLight
{
	float4 color;
	float3 ambient;
	float3 diffuse;
	float3 specular;
	float3 direction;
};


cbuffer PerFrame : register(b0)
{
	DirectionalLight d_Light;
	float3 eyePos;
}

SamplerState samplerState  : SAMPLER : register(s0);
									 
Texture2D diffuseTexture   : TEXTURE : register(t0);
Texture2D specularTexture  : TEXTURE : register(t1);
Texture2D normalTexture    : TEXTURE : register(t2);

//float4 CaculateAmbient()
//{
//	float ambientStrenth = 0.2f;
//	return ambientStrenth * d_Light.color * float4(d_Light.ambient, 1);
//}
//
//float4 CaculateDiffuse(float3 normal, float2 texCoord)
//{
//	float diff = max(dot(normalize(d_Light.direction), normal), 0);
//	return diff * diffuseTexture.Sample(samplerState, texCoord) * float4(d_Light.diffuse, 1);
//}
//
//float4 CaculateSpecular(float3 fragPos, float3 normal, float2 texCoord)
//{
//	float3 eyeDir = normalize(eyePos - fragPos);
//	float3 refDir = reflect(normalize(d_Light.direction), normal);
//	float spec = pow(max(dot(eyeDir, refDir), 0), 64);
//
//	return spec * specularTexture.Sample(samplerState, texCoord) * float4(d_Light.specular, 1);
//}

float4 main(PS_IN ps_in) : SV_TARGET
{
	//float4 t = CaculateAmbient() + CaculateDiffuse(ps_in.normal, ps_in.texcoord) + CaculateSpecular(ps_in.fragPos, ps_in.normal, ps_in.texcoord);
	//float3 result = float3(t.x, t.y, t.z);
	//return float4(result.x, result.y, result.z, 1) * ps_in.color;

	float3 normal = normalTexture.Sample(samplerState, ps_in.texcoord).rgb;


	return normalTexture.Sample(samplerState, ps_in.texcoord);
}