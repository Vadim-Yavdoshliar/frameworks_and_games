
struct VSOut
{
	float2 texPos : TEXCOORD;
	float4 vertexPos : SV_POSITION;
};

struct VSIn {
	float2 pos : POSITION;
	float2 texData : SPRITETEXTURE;
};


VSOut main( VSIn input )
{
	VSOut v;
	v.vertexPos = float4(input.pos.x, input.pos.y, 0.0f, 1.0f);
	v.texPos = float2(input.texData.x,input.texData.y);
	return v;
}



