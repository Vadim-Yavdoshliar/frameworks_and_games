
#ifndef _SPRITE_
#define _SPRITE_

#include "gApp.h"
#include "windowSystem.h"

COM::ComPtr<ID3D11Texture2D> getPictureTexture(const char* filePath);

float getRelPos(float spriteValue,float windowValue);

class Sprite
{
	static std::list<Sprite*>drawableList;
public:
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

void clearBuffersData();

int width, height;
struct vecXY {
	float x = 0;
	float y = 0;
};
struct corner {
	
	vecXY pos;
	vecXY UV;
}; 
struct constantBufStruct {
	XMFLOAT4 translationData = {0,0,0,0};
	XMFLOAT4 rotationData = {0,0,0,0};
	XMFLOAT4 scaleDataAndSize = {0,0,0,0};	
};

constantBufStruct constantBufData;

void updateResources();

bool translationBufferSet = 0;

bool onceDrawn = 0;

corner spriteRectangle[4];

vecXY spritePosition;

public:

	static void drawSprites();

	int getWidth() { return width; }
	int getHeight() { return height; }

	int getX() { return spritePosition.x; }
	int getY() { return spritePosition.y; }

	static void initShaders();
	static void initLayout();
	static void initBlend();

	void setSize(int widthV, int heightV);
	void setPosition(int x, int y);
	void rotate(int angle);


	virtual void draw();

	
	Sprite(const char*);
	Sprite(Sprite*);

	~Sprite();

};





#endif