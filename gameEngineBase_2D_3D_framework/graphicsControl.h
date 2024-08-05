

#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "_conditions.h"



class base_window;

class graphicsControl {

protected:

	COM::ComPtr<ID3D11Device> ppDevice;
	COM::ComPtr<ID3D11DeviceContext> ppContext;
	COM::ComPtr<IDXGISwapChain>ppSwapChain;
	
	base_window* gWindow = nullptr;

public:

	graphicsControl(base_window*);

	virtual ~graphicsControl();

	virtual void showFrame();

};

#endif // !_GRAPHICS_





