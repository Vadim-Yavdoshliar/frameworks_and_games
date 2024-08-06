#include "WinMouse.h"

WinMouse::WinMouse() {

}

WinMouse::keyState WinMouse::getState() {
	return currentKey.state;
}

WinMouse::Coordinate WinMouse::getCoordinate() {
    return mouseCoor;
}

void WinMouse::processKeyMessage(UINT msg, LPARAM lParam, WPARAM wParam) {
 /*if (currentKey.state == WinMouse::Released) 
        currentKey.state = WinMouse::none;*/

    switch (msg)
    {
    case WM_LBUTTONDOWN:
    {
        mouseCoor.x = GET_X_LPARAM(lParam);
        mouseCoor.y = GET_Y_LPARAM(lParam);
        currentKey.state = WinMouse::Pressed;
        break;
    }
    case WM_LBUTTONUP:
    {
        mouseCoor.x = GET_X_LPARAM(lParam);
        mouseCoor.y = GET_Y_LPARAM(lParam);
        currentKey.state = WinMouse::Released;
        break;
    }
    case WM_RBUTTONDOWN:
    {
        mouseCoor.x = GET_X_LPARAM(lParam);
        mouseCoor.y = GET_Y_LPARAM(lParam);
        currentKey.state = WinMouse::Pressed;
        break;
    }
    case WM_RBUTTONUP:
    {
        mouseCoor.x = GET_X_LPARAM(lParam);
        mouseCoor.y = GET_Y_LPARAM(lParam);
        currentKey.state = WinMouse::Released;
        break;
    }
    default:
        break;
    }
   
}

void WinMouse::reviewKeys() {
    static int repeatCounter = 0;
    if (currentKey.state == WinMouse::Released){ 
        ++repeatCounter;
        if (repeatCounter > 3) {
            currentKey.state = WinMouse::none;
            repeatCounter = 0;
        }
    }
	//if (currentKey.state == WinMouse::Released) currentKey.state = WinMouse::none;
}

void WinMouse::clearKey() { currentKey.state = WinMouse::none; }

