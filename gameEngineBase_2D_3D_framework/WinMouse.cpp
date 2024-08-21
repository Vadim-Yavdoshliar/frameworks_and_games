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

void processMouse(gAPP* app) {

#ifdef _INPUT_TEST_

    if (base_window::gameWindow->mainMouse.isLButtonPressed()) {
        if (base_window::gameWindow->getName() != "LPressed") {
            base_window::gameWindow->setTitle("LPressed");
        }
    }
    else if (base_window::gameWindow->mainMouse.isLButtonReleased()) {
        if (base_window::gameWindow->getName() != "LReleased") {
            base_window::gameWindow->setTitle("LReleased");
        }
    }
    else if (base_window::gameWindow->mainMouse.isRButtonPressed()) {
        if (base_window::gameWindow->getName() != "RPressed") {
            base_window::gameWindow->setTitle("RPressed");
        }
    }
    else if (base_window::gameWindow->mainMouse.isRButtonReleased()) {
        if (base_window::gameWindow->getName() != "RReleased") {
            base_window::gameWindow->setTitle("RReleased");
        }
    }
    else if (base_window::gameWindow->mainMouse.isMButtonPressed()) {
        if (base_window::gameWindow->getName() != "MPressed") {
            base_window::gameWindow->setTitle("MPressed");
        }
    }
    else if (base_window::gameWindow->mainMouse.isMButtonReleased()) {
        if (base_window::gameWindow->getName() != "MReleased") {
            base_window::gameWindow->setTitle("MReleased");
        }
    }
    else if (base_window::gameWindow->mainMouse.isSideButtonPressed()) {
        if (base_window::gameWindow->getName() != "SidePressed") {
            base_window::gameWindow->setTitle("SidePressed");
        }
    }
    else if (base_window::gameWindow->mainMouse.isSideButtonReleased()) {
        if (base_window::gameWindow->getName() != "SideReleased") {
            base_window::gameWindow->setTitle("SideReleased");
        }
    }
    else if (base_window::gameWindow->mainMouse.isWheelUp()) {
        if (base_window::gameWindow->getName() != "W up") {
            base_window::gameWindow->setTitle("W up");
        }
    }
    else if (base_window::gameWindow->mainMouse.isWheelDown()) {
        if (base_window::gameWindow->getName() != "W down") {
            base_window::gameWindow->setTitle("W down");
        }
    }
    else {
        if (base_window::gameWindow->getName() != "none") {
            base_window::gameWindow->setTitle("none");
        }
    }
#endif

    if (base_window::gameWindow->mainMouse.isLButtonPressed()) {
        app->mouseKeyPressed(gAPP::LPressed);
    }
    else if (base_window::gameWindow->mainMouse.isLButtonReleased()) {
        app->mouseKeyPressed(gAPP::LReleased);
    }
    else if (base_window::gameWindow->mainMouse.isRButtonPressed()) {
        app->mouseKeyPressed(gAPP::RPressed);
    }
    else if (base_window::gameWindow->mainMouse.isRButtonReleased()) {
        app->mouseKeyPressed(gAPP::RReleased);
    }
    else if (base_window::gameWindow->mainMouse.isMButtonPressed()) {
        app->mouseKeyPressed(gAPP::MPressed);
    }
    else if (base_window::gameWindow->mainMouse.isMButtonReleased()) {
        app->mouseKeyPressed(gAPP::MReleased);
    }
    else if (base_window::gameWindow->mainMouse.isSideButtonPressed()) {
        app->mouseKeyPressed(gAPP::SidePressed);
    }
    else if (base_window::gameWindow->mainMouse.isSideButtonReleased()) {
        app->mouseKeyPressed(gAPP::SideReleased);
    }
    else if (base_window::gameWindow->mainMouse.isWheelUp()) {
        app->mouseKeyPressed(gAPP::WheelUp);
    }
    else if (base_window::gameWindow->mainMouse.isWheelDown()) {
        app->mouseKeyPressed(gAPP::WheelDown);
    }
    else {
        app->mouseKeyPressed(gAPP::none);
    }

}


