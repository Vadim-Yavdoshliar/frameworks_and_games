
#ifndef _SPRITE_
#define _SPRITE_

#include "gApp.h"
#include "windowSystem.h"

COM::ComPtr<ID3D11Texture2D> getPictureTexture(const char* filePath);

float getRelPos(float spriteValue,float windowValue);


class Sprite
{

	static bool initDone;

	COM::ComPtr<ID3D11Texture2D> SpriteTexture;

	COM::ComPtr<ID3D11ShaderResourceView> drawableTexture;

	COM::ComPtr<ID3D11Buffer> spriteVertexBuffer;

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



int width, height;

struct corner {
	float x;
	float y;
};

corner spriteRectangle[4];



public:

	static void initShaders();
	static void initLayout();

	virtual void draw();
	
	void setSize(int widthV, int heightV);
	void setPosition(int xv, int yv);
	void rotate(int angle);

	Sprite(const char*);

	~Sprite();

};





#endif