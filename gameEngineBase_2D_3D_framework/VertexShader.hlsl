
cbuffer TransformationBuf : register(b0) {
    float4 translationData;
    float4 rotationData;
    float4 scaleAndSizeData;
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

float3x3 getTranslationMat(float xv, float yv) {
	
    return float3x3(  1,   0,  0,
					  0,   1,  0,
					  xv,  yv, 1
	);
	
}


VSOut main( VSIn input )
{
	float3 mainVector = { input.pos.x, input.pos.y, 1.0f };
	
    if (translationData.x != 0 || translationData.y != 0)
    {
        mainVector = mul(
		mainVector,
		getTranslationMat(
		translationData.x,
		translationData.y)
		);
        
    }
   // float3 mainVector2 = mul(mainVector, getTranslationMat(1.0f,1.0f));
   
	VSOut v;
    v.vertexPos = float4(mainVector.x, mainVector.y, 0.0f, 1.0f);
	v.texPos = float2(input.texData.x,input.texData.y);
	
	return v;
}



