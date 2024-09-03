
cbuffer TranslationBuf : register(c0) {
	float x;
	float y;
	float z;
	bool checker1;
	bool checker2;
	bool checker3;
};

cbuffer ScaleBuf : register(c1) {
	float x;
	float y;
	float z;
	bool checker1;
	bool checker2;
	bool checker3;
};

cbuffer RotationBuf : register(c2) {
	float x;
	float y;
	float z;
	bool checker1;
	bool checker2;
	bool checker3;
};


struct VSOut
{
	float4 vertexPos : SV_POSITION;
	float2 texPos : TEXCOORD;
};

struct VSIn {
	float2 pos : POSITION;
	float2 texData : SPRITETEXTURE;

};

float3x3 translationMat(float x, float y) {

}

float3x3 scaleMat(float x, float y) {

}

float3x3 rotation_x(float y, float z) {

}

float3x3 rotation_y(float x, float z) {

}

float3x3 rotation_z(float x, float y) {

}

VSOut main( VSIn input )
{
	float3 mainVector(input.pos.x, input.pos.y, 0.0f);

	if (TranslationBuf.checker1) {
		mainVector = mul(TranslationBuf.x, TranslationBuf.y, TranslationBuf.z);
	}

	VSOut v;
	v.vertexPos = float4(input.pos.x, input.pos.y, 0.0f, 1.0f);
	v.texPos = float2(input.texData.x,input.texData.y);
	
	return v;
}



