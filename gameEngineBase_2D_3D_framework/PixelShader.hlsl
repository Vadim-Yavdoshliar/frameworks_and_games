
Texture2D tex : register(t0);
SamplerState ss;

struct PSIn
{
	float4 vertexPos : SV_POSITION;
	float2 texPos : TEXCOORD;
};

float4 main(PSIn data) : SV_Target
{
	return tex.Sample(ss,data.texPos);
}