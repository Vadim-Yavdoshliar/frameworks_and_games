

#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "_conditions.h"



class base_window;

class graphicsControl {

protected:

	COM::ComPtr<ID3D11Device> ppDevice;
	COM::ComPtr<ID3D11DeviceContext> ppContext;
	COM::ComPtr<IDXGISwapChain> ppSwapChain;

	COM::ComPtr<ID3D11Texture2D> backBufferTexture;
	COM::ComPtr<ID3D11RenderTargetView> backBuffer;
	COM::ComPtr<ID3D11InputLayout> vertexInputLayout;
	COM::ComPtr<ID3D11SamplerState> sampler;

	base_window* gWindow = nullptr;

public:

	COM::ComPtr<ID3D11InputLayout>& getVertexInputLayout();
	COM::ComPtr<ID3D11Device> getDevice();
	COM::ComPtr<ID3D11DeviceContext> getControl();
	COM::ComPtr<IDXGISwapChain> getppSwapChain();
	COM::ComPtr<ID3D11RenderTargetView> getTargetView();


	void startFrame();
	void processFrame();
	void endFrame();

	graphicsControl(base_window*);

	virtual ~graphicsControl();

	virtual void showFrame();

};

#endif // !_GRAPHICS_






