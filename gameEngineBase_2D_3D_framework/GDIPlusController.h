#pragma once
#include "Sprite.h"

using namespace Gdiplus;

class GDIPlusController {
public:

    GDIPlusController();

    ~GDIPlusController();

    static GDIPlusController& getInstance() {
        static GDIPlusController instance;
        return instance;
    }

private:

    ULONG_PTR gdiplusToken;
};

//void initPicture();
void initGDIPlus();