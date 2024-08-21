#include "graphicsControl.h"
#include "windowSystem.h"

COM::ComPtr<ID3D11Device> graphicsControl::getDevice()
{
	return ppDevice;
}
COM::ComPtr<ID3D11DeviceContext> graphicsControl::getControl()
{
	return ppContext;
}
COM::ComPtr<ID3D11InputLayout>& graphicsControl::getVertexInputLayout()
{
	return vertexInputLayout;
}
COM::ComPtr<IDXGISwapChain> graphicsControl::getppSwapChain()
{
	return ppSwapChain;
}
COM::ComPtr<ID3D11RenderTargetView> graphicsControl::getTargetView()
{
	return backBuffer;
}
graphicsControl::graphicsControl(base_window* winInst)
{

	HRESULT hr;

	gWindow = winInst;
	if (gWindow != nullptr) {

		DXGI_SWAP_CHAIN_DESC textureDesc = {};
		
		textureDesc.BufferDesc.Width = 0;
		textureDesc.BufferDesc.Height = 0;
		textureDesc.BufferDesc.RefreshRate.Numerator = 60;
		textureDesc.BufferDesc.RefreshRate.Denominator = 1;
		textureDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		textureDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		textureDesc.BufferCount = 1;
		textureDesc.OutputWindow = gWindow->getWND();
		textureDesc.Windowed = TRUE;
		textureDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		textureDesc.Flags = 0;
		


		hr = D3D11CreateDeviceAndSwapChain(
				NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				NULL,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&textureDesc,
				&ppSwapChain,
				&ppDevice,
				NULL,
				&ppContext
			);
		
		if (FAILED(hr)) myEXC("Error while creating device and other initial tools")



		hr = ppSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBufferTexture);
		if (FAILED(hr))	myEXC("problem with back buffer getting")

		hr = ppDevice->CreateRenderTargetView
			(
				backBufferTexture.Get(),
				nullptr,
				&backBuffer
			);
	
		if (FAILED(hr))	myEXC("problem with back buffer target creating")

			ppContext->OMSetRenderTargets(
				1,
			backBuffer.GetAddressOf(),
				nullptr);

		ppContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


		D3D11_VIEWPORT vp;
		vp.Width = gWindow->getWidth();
		vp.Height = gWindow->getHeight();
		vp.MinDepth = 0;
		vp.MaxDepth = 1;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;

		ppContext->RSSetViewports(1, &vp);

		D3D11_SAMPLER_DESC samplerDesc = {};

		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		hr = ppDevice->CreateSamplerState(
			&samplerDesc,
			&sampler);

		if (FAILED(hr)) {
			myEXC("sampler creation issue")
		}

		ppContext->PSSetSamplers(
			0, 
			1, 
			sampler.GetAddressOf());
	}
}

void graphicsControl::startFrame()
{

	float color[4] = { 1.0f, 0.0f, 1.0, 0.0f };
    ppContext->ClearRenderTargetView(backBuffer.Get(), color);

}

graphicsControl::~graphicsControl()
{
	
}


void graphicsControl::showFrame()
{

	ppSwapChain->Present(1u, 0);
}



