#include "Sprite.h"


<<<<<<< Updated upstream
Sprite* createSprite(const char*) { return nullptr; }
void getSpriteSize(int& x, int& y) {}
void drawSprite(Sprite*) {}
void resizeSprite(Sprite*, int width, int heith) {}
void rotateSprite(Sprite*) {}
<<<<<<< HEAD
void replaceSprite(Sprite*) {}
=======
void replaceSprite(Sprite*) {}
=======
void rotateSprite(Sprite* init, int angle) {
	init->rotate(angle);
}

void setSpritePosition(Sprite* inst, int x, int y)
{
	if (inst != nullptr) {
		inst->setPosition(x, y);
	}
}

>>>>>>> Stashed changes

Sprite::SpriteVertexShader Sprite::SpriteVertexShader::initialUnit;

Sprite::SpritePixelShader Sprite::SpritePixelShader::initialUnit;

bool Sprite::initDone = 0;

float getRelPos(float spriteValue, float windowValue)
{
	return ((2 * spriteValue) / windowValue) - 1;
}




Sprite::Sprite(const char* fileName)
{

	HRESULT hr;

	SpriteTexture = getPictureTexture(fileName);

	if (SpriteTexture == nullptr) {
		myBoxMessage("cant load the image", "External file problem")
			myEXC("problem with creating sprite while loading the image")
	}

	D3D11_TEXTURE2D_DESC spriteTextureDesciption;
	SpriteTexture.Get()->GetDesc(&spriteTextureDesciption);

	width = spriteTextureDesciption.Width;
	height = spriteTextureDesciption.Height;


	spriteRectangle[0] = { { -1,1 },{0,0} };
	spriteRectangle[1] = {
		{getRelPos
		(
			width,
			base_window::gameWindow->getWidth()
		),
		1},
		{1,0}
	};
	spriteRectangle[2] = {
		{ -1,
		-getRelPos
		(
			height,
			base_window::gameWindow->getHeight()
		)},
		{0,1}
	};
	spriteRectangle[3] = {
		{getRelPos
		(
			width,
			base_window::gameWindow->getWidth()
		),
		-getRelPos
		(
			height,
			base_window::gameWindow->getHeight()
		)},
		{1,1}
	};


	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.ByteWidth = sizeof(spriteRectangle);
	buffer_desc.StructureByteStride = sizeof(corner);
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA actualVertexData = {};
	actualVertexData.pSysMem = spriteRectangle;

	hr = gw_device->CreateBuffer(
		&buffer_desc,
		&actualVertexData,
		&spriteVertexBuffer
	);
	
	if (!FAILED(hr)) {

		UINT step = sizeof(corner);
		UINT offset = 0;

		gw_context->IASetVertexBuffers(
			0,
			1,
			spriteVertexBuffer.GetAddressOf(),
			&step,
			&offset
		);
	}
	else myEXC("Vertex BUFFER creation issue")

		D3D11_SHADER_RESOURCE_VIEW_DESC textureDesc = {};

	textureDesc.Format = spriteTextureDesciption.Format;
	textureDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	textureDesc.Texture2D.MostDetailedMip = 0;
	textureDesc.Texture2D.MipLevels = 1;

	hr = gw_device->CreateShaderResourceView(
		SpriteTexture.Get(),
		&textureDesc,
		&drawableTexture
	);
	


	if (FAILED(hr)) myEXC("Problem with shader resource view creation")


		gw_context->PSSetShaderResources(
			0,
			1,
			drawableTexture.GetAddressOf());


}


void initSpriteCreation() {

	

	Sprite::initShaders();
	
	Sprite::initLayout();
	Sprite::initBlend();
	
}

void Sprite::SpriteVertexShader::initVertexShader()
{
	if (initialUnit.mainShader != nullptr) return;
	HRESULT hr = D3DReadFileToBlob(L"VertexShader.cso", &initialUnit.shaderBinaryShape);
	if (!FAILED(hr)) {


		hr = gw_device->CreateVertexShader(
			initialUnit.shaderBinaryShape->GetBufferPointer(),
			initialUnit.shaderBinaryShape->GetBufferSize(),
			0,
			&initialUnit.mainShader
		);
		if (!FAILED(hr)) {
			gw_context->VSSetShader(initialUnit.mainShader.Get(), nullptr, 0);
		}
		else myEXC("Vertex shader creation issue")
	}
	else myEXC("Vertex shader loading issue")
}

COM::ComPtr<ID3DBlob> Sprite::SpriteVertexShader::getVertexShaderBinary()
{
	return initialUnit.shaderBinaryShape;
}


void Sprite::SpritePixelShader::initPixelShader() {

	if (initialUnit.mainShader != nullptr) return;
	HRESULT hr = D3DReadFileToBlob(L"PixelShader.cso", &initialUnit.shaderBinaryShape);
	if (!FAILED(hr)) {


		hr = gw_device->CreatePixelShader(
			initialUnit.shaderBinaryShape->GetBufferPointer(),
			initialUnit.shaderBinaryShape->GetBufferSize(),
			0,
			&initialUnit.mainShader
		);
		if (!FAILED(hr)) {
			gw_context->PSSetShader(initialUnit.mainShader.Get(), nullptr, 0);
		}
		else myEXC("Pixel shader creation issue")
	}
	else myEXC("Pixel shader loading issue")
}

<<<<<<< Updated upstream
=======

void Sprite::setSize(int widthV, int heightV)
{
	width = widthV;
	height = heightV;
}

void Sprite::setPosition(int x, int y)
{
	if (onceDrawn) {
		if (x == spritePosition.x && y == spritePosition.y) {
			return;
		}
	}
	

	translationBufferSet = 1;

	constantBufData.translationData = {
		getRelPos(x,base_window::gameWindow->getWidth())
		-getRelPos(spritePosition.x, base_window::gameWindow->getWidth()),
		-getRelPos(y,base_window::gameWindow->getHeight())
		+getRelPos(spritePosition.y, base_window::gameWindow->getHeight()),
			0,0 };

	spritePosition.x = x;
	spritePosition.y = y;

	onceDrawn = 1;
}

void Sprite::updateResources() {

	if (translationBufferSet) {
		D3D11_MAPPED_SUBRESOURCE mappedResource = {};

		gw_context->Map(
			constantBuff.Get(),
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&mappedResource);

		memcpy(mappedResource.pData,
			&constantBufData,
			sizeof(constantBufStruct));


		gw_context->Unmap(constantBuff.Get(), 0);

		translationBufferSet = 0;
	}
}


void Sprite::rotate(int angle)
{
	if (onceDrawn) {
		if (angle== spriteCurrAngle) {
			return;
		}
	}
	spriteCurrAngle = angle%360;
	translationBufferSet = 1;

	float t1 = getRelPos(base_window::gameWindow->getWidth()/2-getWidth()/2, base_window::gameWindow->getWidth())
		- getRelPos(spritePosition.x, base_window::gameWindow->getWidth());
	float t2 = -getRelPos(base_window::gameWindow->getHeight()/2 - getHeight() / 2, base_window::gameWindow->getHeight())
		+ getRelPos(spritePosition.y, base_window::gameWindow->getHeight());

	constantBufData.rotationData = { t1,t2,XMConvertToRadians(angle),3};
	onceDrawn = 1;
}


void Sprite::drawSprites()
{
	for (auto& s : drawableList) {
		if (s != nullptr) {
			s->draw();
		}
	}
}

>>>>>>> Stashed changes
void Sprite::initShaders()
{
	if (initDone != 0) return;

	Sprite::SpriteVertexShader::initVertexShader();
	Sprite::SpritePixelShader::initPixelShader();

}

void Sprite::initLayout()
{
	if (initDone != 0) return;
	HRESULT hr;
	COM::ComPtr<ID3D11InputLayout> vertexInputLayout;


	D3D11_INPUT_ELEMENT_DESC vertexPosInputDecs = {};
	vertexPosInputDecs.SemanticName = "POSITION";
	vertexPosInputDecs.SemanticIndex = 0;
	vertexPosInputDecs.Format = DXGI_FORMAT_R32G32_FLOAT;
	vertexPosInputDecs.InputSlot = 0;
	vertexPosInputDecs.AlignedByteOffset = 0;
	vertexPosInputDecs.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	vertexPosInputDecs.InstanceDataStepRate = 0;

	D3D11_INPUT_ELEMENT_DESC vertexTexInputDecs = {};
	vertexTexInputDecs.SemanticName = "SPRITETEXTURE";
	vertexTexInputDecs.SemanticIndex = 0;
	vertexTexInputDecs.Format = DXGI_FORMAT_R32G32_FLOAT;
	vertexTexInputDecs.InputSlot = 0;
	vertexTexInputDecs.AlignedByteOffset = 8;
	vertexTexInputDecs.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	vertexTexInputDecs.InstanceDataStepRate = 0;

	D3D11_INPUT_ELEMENT_DESC layoutDecsList[] = 
	{ vertexPosInputDecs ,vertexTexInputDecs };

	int layoutCount = std::size(layoutDecsList);

	COM::ComPtr<ID3D11InputLayout> t_layout;

	hr = gw_device->CreateInputLayout(
		layoutDecsList,
		layoutCount,
		Sprite::SpriteVertexShader::getVertexShaderBinary()->GetBufferPointer(),
		Sprite::SpriteVertexShader::getVertexShaderBinary()->GetBufferSize(),
		&t_layout
		);

	if (FAILED(hr)) {
		myEXC("Problem with layout creation")
	}

	gw_context->IASetInputLayout(
		t_layout.Get());


	gw_object->graphicsStation->getVertexInputLayout() = t_layout;

	initDone = 1;
}

void Sprite::initBlend() {
	ID3D11BlendState* g_pBlendStateNoBlend = NULL;

	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; 
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; 

	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; 
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; 
	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; 

	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; 

	HRESULT hr = gw_device->CreateBlendState(&BlendState, &g_pBlendStateNoBlend);
	if (FAILED(hr)) {
		myEXC("Problem with blend creation")
	}
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	UINT sampleMask = 0xffffffff;

	gw_context->OMSetBlendState(g_pBlendStateNoBlend, blendFactor, sampleMask);
}


void Sprite::draw()
{
	gw_context->Draw(4,0);
	
}
>>>>>>> ed13ef4 (Sprite transparency)
