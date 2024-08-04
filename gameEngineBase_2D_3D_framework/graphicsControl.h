

#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "_conditions.h"

class base_window;



class graphicsControl {

protected:

	ID3D11Device* ppDevice = nullptr;
	ID3D11DeviceContext* ppContext = nullptr;
	IDXGISwapChain* ppSwapChain = nullptr;
	
	base_window* gWindow = nullptr;

public:

	graphicsControl(base_window*);

	virtual ~graphicsControl();

	virtual void showFrame();

};

#endif // !_GRAPHICS_






