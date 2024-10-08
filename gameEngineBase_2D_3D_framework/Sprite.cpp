#include "Sprite.h"


Sprite* createSprite(const char* path) { return new Sprite(path); }
void getSpriteSize(int& x, int& y) {}
void drawSprite(Sprite* inst,int x,int y) {
	inst->draw();
}
void resizeSprite(Sprite*, int width, int heith) {}
void rotateSprite(Sprite*) {}
void replaceSprite(Sprite*) {}

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


void Sprite::draw()
{
	gw_context->Draw(4,0);
	
}