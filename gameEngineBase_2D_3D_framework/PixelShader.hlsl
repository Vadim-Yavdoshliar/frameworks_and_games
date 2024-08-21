
Texture2D tex;
SamplerState ss;

float4 main(float2 inCoord : TEXCOORD) : SV_Target
{
	return tex.Sample(ss,inCoord);
}