//#include "WinMouse.h"
#include "windowSystem.h"

WinMouse::WinMouse() {

}

void WinMouse::clearBuffer() {
    while (!buffer.empty()) {
        buffer.pop();
    }
}
void WinMouse::IfBufferIsFool() {
    while (buffer.size() >= MAXBUFFERSIZE) {
        buffer.pop();
    }
}

void WinMouse::OnPressed(keyState key) {
    if (!buffer.empty()) {
        buffer.pop();
    }
    buffer.push(key);
}

void WinMouse::OnReleased(keyState key){
    if (!buffer.empty()) {
        if (buffer.front() == key) buffer.pop();
    }
}

WinMouse::Coordinate WinMouse::getMouseCoordinate() {
    return mouseCoordinate;
}

int WinMouse::getXmouseCoordinate() {
    return mouseCoordinate.x;
}

int WinMouse::getYmouseCoordinate() {
    return mouseCoordinate.y;
}

bool WinMouse::isLButtonPressed() {
    if(!buffer.empty()) return (buffer.front() == LPressed) ? true : false;
    return false;
}

bool WinMouse::isLButtonReleased(){
    if (!buffer.empty()) {
        if ((buffer.front() == LReleased)) {
            buffer.pop();
            return true;
        }
    }
    return false;
}


bool WinMouse::isRButtonPressed() {
    if (!buffer.empty()) return (buffer.front() == RPressed) ? true : false;
    return false;
}

bool WinMouse::isRButtonReleased() {
    if (!buffer.empty()) {
        if ((buffer.front() == RReleased)) {
            buffer.pop();
            return true;
        }
    }
    return false;
}


bool WinMouse::isSideButtonPressed() {
    if (!buffer.empty()) return (buffer.front() == SidePressed) ? true : false;
    return false;
}

bool WinMouse::isSideButtonReleased() {
    if (!buffer.empty()) {
        if ((buffer.front() == SideReleased)) {
            buffer.pop();
            return true;
        }
    }
    return false;
}

bool WinMouse::isMButtonPressed() {
    if (!buffer.empty()) return (buffer.front() == MPressed) ? true : false;
    return false;
}

bool WinMouse::isMButtonReleased() {
    if (!buffer.empty()) {
        if ((buffer.front() == MReleased)) {
            buffer.pop();
            return true;
        }
    }
    return false;
}

bool WinMouse::isWheelUp() {
    int res = false;
    if (scrollDelta > 0) {
        scrollDelta = 0;
        res = true;
    }
    return res;
}
bool WinMouse::isWheelDown() {
    int res = false;
    if (scrollDelta < 0) {
        scrollDelta = 0;
        res = true;
    }
    return res;
}


void WinMouse::processKeyMessage(UINT msg, LPARAM lParam, WPARAM wParam) {
    if (mouseIsAvailable) {
        
        switch (msg)
        {
        case WM_LBUTTONDOWN:
        {
            OnPressed(LPressed);
            buffer.push(LReleased);
            IfBufferIsFool();
            mouseCoordinate.x = GET_X_LPARAM(lParam);
            mouseCoordinate.y = GET_Y_LPARAM(lParam);
            break;
        }
        case WM_LBUTTONUP:
        {
            OnReleased(LPressed);
            mouseCoordinate.x = GET_X_LPARAM(lParam);
            mouseCoordinate.y = GET_Y_LPARAM(lParam);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            OnPressed(RPressed);
            buffer.push(RReleased);
            IfBufferIsFool();
            mouseCoordinate.x = GET_X_LPARAM(lParam);
            mouseCoordinate.y = GET_Y_LPARAM(lParam);
            break;
        }
        case WM_RBUTTONUP:
        {
            OnReleased(RPressed);
            mouseCoordinate.x = GET_X_LPARAM(lParam);
            mouseCoordinate.y = GET_Y_LPARAM(lParam);
            break;
        }
        case WM_MBUTTONDOWN:
        {
            OnPressed(MPressed);
            buffer.push(MReleased);
            IfBufferIsFool();
            mouseCoordinate.x = GET_X_LPARAM(lParam);
            mouseCoordinate.y = GET_Y_LPARAM(lParam);
            break;
        }
        case WM_MBUTTONUP:
        {
            OnReleased(MPressed);
            mouseCoordinate.x = GET_X_LPARAM(lParam);
            mouseCoordinate.y = GET_Y_LPARAM(lParam);
            break;
        }
        case WM_XBUTTONDOWN:
        {
            OnPressed(SidePressed);
            buffer.push(SideReleased);
            IfBufferIsFool();
            mouseCoordinate.x = GET_X_LPARAM(lParam);
            mouseCoordinate.y = GET_Y_LPARAM(lParam);
            break;
        }
        case WM_XBUTTONUP:
        {
            OnReleased(SidePressed);
            mouseCoordinate.x = GET_X_LPARAM(lParam);
            mouseCoordinate.y = GET_Y_LPARAM(lParam);
            break;
        }
        case WM_MOUSEMOVE:
        {
            mouseCoordinate.x = GET_X_LPARAM(lParam);
            mouseCoordinate.y = GET_Y_LPARAM(lParam);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            scrollDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        }
        default:
            break;
        }
    }
}

void processMouse(base_window* win) {
    if (win->mainMouse.isLButtonPressed()) {
        if (win->getName() != "LPressed") {
            win->setTitle("LPressed");
        }
    }
    else if (win->mainMouse.isLButtonReleased()) {
        if (win->getName() != "LReleased") {
            win->setTitle("LReleased");
        }
    }
    else if (win->mainMouse.isRButtonPressed()) {
        if (win->getName() != "RPressed") {
            win->setTitle("RPressed");
        }
    }
    else if (win->mainMouse.isRButtonReleased()) {
        if (win->getName() != "RReleased") {
            win->setTitle("RReleased");
        }
    }
    else if (win->mainMouse.isMButtonPressed()) {
        if (win->getName() != "MPressed") {
            win->setTitle("MPressed");
        }
    }
    else if (win->mainMouse.isMButtonReleased()) {
        if (win->getName() != "MReleased") {
            win->setTitle("MReleased");
        }
    }
    else if (win->mainMouse.isSideButtonPressed()) {
        if (win->getName() != "SidePressed") {
            win->setTitle("SidePressed");
        }
    }
    else if (win->mainMouse.isSideButtonReleased()) {
        if (win->getName() != "SideReleased") {
            win->setTitle("SideReleased");
        }
    }
    else if (win->mainMouse.isWheelUp()) {
        if (win->getName() != "W up") {
            win->setTitle("W up");
        }
    }
    else if (win->mainMouse.isWheelDown()) {
        if (win->getName() != "W down") {
            win->setTitle("W down");
        }
    }
    else {
        if (win->getName() != "none") {
            win->setTitle("none");
        }
    }
}


