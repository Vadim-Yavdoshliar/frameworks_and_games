#include "graphicsControl.h"
#include "windowSystem.h"
graphicsControl::graphicsControl(base_window* winInst)
{
	gWindow = winInst;
	if (gWindow != nullptr) {

		DXGI_SWAP_CHAIN_DESC textureDesc = {};
		
		textureDesc.BufferDesc.Width = 0;
		textureDesc.BufferDesc.Height = 0;
		textureDesc.BufferDesc.RefreshRate.Numerator = 0;
		textureDesc.BufferDesc.RefreshRate.Denominator = 0;
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
		


		D3D11CreateDeviceAndSwapChain(
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
	}
}

graphicsControl::~graphicsControl()
{
	
	if (ppContext != nullptr) ppContext->Release();
	if (ppSwapChain != nullptr) ppSwapChain->Release();
	if (ppDevice != nullptr) ppDevice->Release();
}

void graphicsControl::showFrame()
{
	ppSwapChain->Present(1u, 0);
}
