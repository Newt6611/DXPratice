#define MAX_POINT_LIGHT 4

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
	float3 ambient;
	float3 diffuse;
	float3 specular;
	float3 direction;
};

struct PointLight
{
	float4 color;
	float3 position;
	float constant;

	float3 ambient;
	float m_linear;
	
	float3 diffuse;
	float quadratic;
	
	float3 specular;
};


cbuffer PerFrame : register(b0)
{
	DirectionalLight d_Light;
	PointLight p_Light[MAX_POINT_LIGHT];
	float3 eyePos;
}

SamplerState samplerState  : SAMPLER : register(s0);

Texture2D diffuseTexture   : TEXTURE : register(t0);
Texture2D specularTexture  : TEXTURE : register(t1);
Texture2D normalTexture    : TEXTURE : register(t2);
Texture2D depthTexture     : TEXTURE : register(t3);



float4 DoDirectionalLight(float3 fragPos, float3 normal, float2 texCoord)
{
	// ambient
	float ambientStrenth = 0.2f;
	float4 ambient = ambientStrenth * d_Light.color * float4(d_Light.ambient, 1);

	// diffuse
	float diff = max(dot(normalize(-d_Light.direction), normal), 0);
	float4 diffuse = diff * diffuseTexture.Sample(samplerState, texCoord) * float4(d_Light.diffuse, 1);

	// specular
	float3 eyeDir = normalize(eyePos - fragPos);
	
	// blinn
	float3 halfwayDir = normalize(eyeDir + (-d_Light.direction));
	float spec = pow(max(dot(normal, halfwayDir), 0), 64);
	float4 specular = spec * specularTexture.Sample(samplerState, texCoord) * float4(d_Light.specular, 1);

	return ambient + diffuse + specular;
}

float4 DoPointLight(float3 fragPos, float3 normal, float2 texCoord)
{
	float4 total = float4(0, 0, 0, 0);

	for (int i = 0; i < MAX_POINT_LIGHT; i++)
	{
		float distance = length(p_Light[i].position - fragPos);
		float attenuation = 1.0 / (p_Light[i].constant + p_Light[i].m_linear + p_Light[i].quadratic * (distance * distance));
		float3 lightDir = normalize(p_Light[i].position - fragPos);


		// ambient
		float ambientStrenth = 0.2f;
		float4 ambient = ambientStrenth * p_Light[i].color * float4(p_Light[i].ambient, 1) * attenuation;

		// diffuse
		float diff = max(dot(lightDir, normal), 0);
		float4 diffuse = diff * diffuseTexture.Sample(samplerState, texCoord) * float4(p_Light[i].diffuse, 1) * attenuation;

		// specular
		float3 eyeDir = normalize(eyePos - fragPos);

		// blinn
		float3 halfwayDir = normalize(eyeDir + lightDir);
		float spec = pow(max(dot(halfwayDir, normal), 0), 64);
		float4 specular = spec * specularTexture.Sample(samplerState, texCoord) * float4(p_Light[i].specular, 1) * attenuation;
		
		total += ambient + diffuse + specular;
	}
	
	return total;
}

float4 main(PS_IN ps_in) : SV_TARGET
{
	float4 result = DoPointLight(ps_in.fragPos, ps_in.normal, ps_in.texcoord);
	result += DoDirectionalLight(ps_in.fragPos, ps_in.normal, ps_in.texcoord);
	return float4(result.x, result.y, result.z, 1) * ps_in.color;
	//return depthTexture.Sample(samplerState, ps_in.texcoord);
}