#include "WinMouse.h"

WinMouse::WinMouse() {

}

int WinMouse::getScrollDelta() {
    return scrollDelta;
}

WinMouse::keyState WinMouse::getRightKeyState() {
    return rightKey.state;
}

WinMouse::keyState WinMouse::getLeftKeyState() {
    return leftKey.state;
}

WinMouse::keyState WinMouse::getMiddleKeyState() {
    return middleKey.state;
}

WinMouse::keyState WinMouse::getSideKeyState() {
    return sideKey.state;
}

WinMouse::Coordinate WinMouse::getRightKeyCoordinate() {
    return rightKey.keyCoordinate;
}

WinMouse::Coordinate WinMouse::getLeftKeyCoordinate() {
    return leftKey.keyCoordinate;
}

WinMouse::Coordinate WinMouse::getMiddleKeyCoordinate() {
    return middleKey.keyCoordinate;
}

WinMouse::Coordinate WinMouse::getSideKeyCoordinate() {
    return sideKey.keyCoordinate;
}

void WinMouse::processKeyMessage(UINT msg, LPARAM lParam, WPARAM wParam) {
    switch (msg)
    {
    case WM_LBUTTONDOWN:
    {
        leftKey.keyCoordinate.x = GET_X_LPARAM(lParam);
        leftKey.keyCoordinate.y = GET_Y_LPARAM(lParam);
        leftKey.state = WinMouse::Pressed;
        break;
    }
    case WM_LBUTTONUP:
    {
        leftKey.keyCoordinate.x = GET_X_LPARAM(lParam);
        leftKey.keyCoordinate.y = GET_Y_LPARAM(lParam);
        leftKey.state = WinMouse::Released;
        break;
    }
    case WM_RBUTTONDOWN:
    {
        rightKey.keyCoordinate.x = GET_X_LPARAM(lParam);
        rightKey.keyCoordinate.y = GET_Y_LPARAM(lParam);
        rightKey.state = WinMouse::Pressed;
        break;
    }
    case WM_RBUTTONUP:
    {
        rightKey.keyCoordinate.x = GET_X_LPARAM(lParam);
        rightKey.keyCoordinate.y = GET_Y_LPARAM(lParam);
        rightKey.state = WinMouse::Released;
        break;
    }
    case WM_MBUTTONDOWN:
    {
        middleKey.keyCoordinate.x = GET_X_LPARAM(lParam);
        middleKey.keyCoordinate.y = GET_Y_LPARAM(lParam);
        middleKey.state = WinMouse::Pressed;
        break;
    }
    case WM_MBUTTONUP:
    {
        middleKey.keyCoordinate.x = GET_X_LPARAM(lParam);
        middleKey.keyCoordinate.y = GET_Y_LPARAM(lParam);
        middleKey.state = WinMouse::Released;
        break;
    }
    case WM_XBUTTONDOWN:
    {
        sideKey.keyCoordinate.x = GET_X_LPARAM(lParam);
        sideKey.keyCoordinate.y = GET_Y_LPARAM(lParam);
        sideKey.state = WinMouse::Pressed;
        break;
    }
    case WM_XBUTTONUP:
    {
        sideKey.keyCoordinate.x = GET_X_LPARAM(lParam);
        sideKey.keyCoordinate.y = GET_Y_LPARAM(lParam);
        sideKey.state = WinMouse::Released;
        break;
    }
    case WM_MOUSEMOVE:
    {
        if (wParam & MK_LBUTTON) {
            leftKey.keyCoordinate.x = GET_X_LPARAM(lParam);
            leftKey.keyCoordinate.y = GET_Y_LPARAM(lParam);
            leftKey.state = WinMouse::Held;
        }
        break;
    }
    case WM_MOUSEWHEEL:
    {
        scrollDelta += GET_WHEEL_DELTA_WPARAM(wParam);
        break;
    }
    default:
        if (wParam & MK_LBUTTON) {
            if (leftKey.state == WinMouse::Pressed) leftKey.state = WinMouse::Held;
        }
        if (wParam & MK_RBUTTON) {
            if (rightKey.state == WinMouse::Pressed) rightKey.state = WinMouse::Held;
        }
        if (wParam & MK_MBUTTON) {
            if (middleKey.state == WinMouse::Pressed) middleKey.state = WinMouse::Held;
        }
        if (wParam & MK_XBUTTON1) {
            if (sideKey.state == WinMouse::Pressed) sideKey.state = WinMouse::Held;
        }
        if (wParam & MK_XBUTTON2) {
            if (sideKey.state == WinMouse::Pressed) sideKey.state = WinMouse::Held;
        }
        break;
    }


}

void WinMouse::reviewKeys() {
    if (rightKey.state == WinMouse::Released) rightKey.state = WinMouse::none;
    if (leftKey.state == WinMouse::Released) leftKey.state = WinMouse::none;
    if (middleKey.state == WinMouse::Released) middleKey.state = WinMouse::none;
    if (sideKey.state == WinMouse::Released) sideKey.state = WinMouse::none;
}

