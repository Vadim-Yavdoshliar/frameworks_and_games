
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

float3x3 rotation_x(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return float3x3(
        1.0f, 0.0f, 0.0f,
        0.0f,  c, -s,
        0.0f, s, c
    );
}

float3x3 rotation_y(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return float3x3(
        c, 0.0f, s,
        0.0f,  1.0f, 0.0f,
        -s, 0.0f, c
    );
}

float3x3 rotation_z(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return float3x3(
        c, -s, 0.0f,
        s,  c, 0.0f,
        0.0f, 0.0f, 1.0f
    );
}

float3x3 aspectRatioCorrection(float aspect)
{
    return float3x3(
        1.0f /aspect, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
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
    if (rotationData.z != 0)
    {
       
        mainVector = mul(
		mainVector,
		getTranslationMat(
		rotationData.x,
		rotationData.y)
		);
        mainVector = mul(mainVector, aspectRatioCorrection(700.0f / 800.0f));
        if (rotationData.w == 3)
        {
            mainVector = mul(mainVector, rotation_z(rotationData.z));
        }
        mainVector = mul(mainVector, aspectRatioCorrection(800.0f / 700.0f));
        mainVector = mul(
		mainVector,
		getTranslationMat(
		-rotationData.x,
		-rotationData.y)
		);
        
    }
    
    
	VSOut v;
    v.vertexPos = float4(mainVector.x, mainVector.y, 0.0f, 1.0f);
	v.texPos = float2(input.texData.x,input.texData.y);
	
	return v;
}



