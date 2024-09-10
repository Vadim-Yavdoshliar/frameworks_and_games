
#ifndef _SPRITE_
#define _SPRITE_

#include "gApp.h"
#include "windowSystem.h"

COM::ComPtr<ID3D11Texture2D> getPictureTexture(const char* filePath);



class Sprite
{

public:
<<<<<<< Updated upstream
=======
	bool drawable = 0;
private:

	// SHADERS
class SpriteVertexShader {

	SpriteVertexShader() = default;

	COM::ComPtr<ID3D11VertexShader> mainShader;
	COM::ComPtr<ID3DBlob> shaderBinaryShape;
	
	static SpriteVertexShader initialUnit;

public:

	static void initVertexShader();

	static COM::ComPtr<ID3DBlob> getVertexShaderBinary();
	static COM::ComPtr<ID3D11VertexShader> getSpriteVertexShader();
};

class SpritePixelShader {

	SpritePixelShader() = default;

	COM::ComPtr<ID3D11PixelShader> mainShader;
	COM::ComPtr<ID3DBlob> shaderBinaryShape;

	static SpritePixelShader initialUnit;

public:

	static void initPixelShader();

	static COM::ComPtr<ID3DBlob> getPixelShaderBinary();
	static COM::ComPtr<ID3D11VertexShader> getSpritePixelShader();
};

	// Shows that general graphics resources are set for sprites drawing
static bool initDone;

	// MAIN SPRITE DATA

COM::ComPtr<ID3D11Buffer> constantBuff;

COM::ComPtr<ID3D11Texture2D> SpriteTexture;

COM::ComPtr<ID3D11ShaderResourceView> drawableTexture;

COM::ComPtr<ID3D11Buffer> spriteVertexBuffer;

int width, height;
struct vecXY {
	float x = 0;
	float y = 0;
};
struct corner {
>>>>>>> Stashed changes
	
<<<<<<< HEAD
=======
	vecXY pos;
	vecXY UV;
<<<<<<< Updated upstream
=======
}; 
struct constantBufStruct {
	XMFLOAT4 translationData = {0,0,0,0};
	/// <summary>
	/// {float x,float y,float angle,float rotation by x=1,y=2,z=3}
	/// </summary>
	XMFLOAT4 rotationData = {0,0,0,0};
	XMFLOAT4 scaleDataAndSize = {0,0,0,0};	
>>>>>>> Stashed changes
};

corner spriteRectangle[4];



int spriteCurrAngle = 0;

public:

	static void initShaders();
	static void initLayout();
	static void initBlend();

	virtual void draw();
>>>>>>> ed13ef4 (Sprite transparency)
	
	Sprite(const char*);

	~Sprite();

};





#endif