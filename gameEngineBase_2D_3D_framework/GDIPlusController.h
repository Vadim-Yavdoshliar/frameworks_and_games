#pragma once
#include "Sprite.h"

using namespace Gdiplus;

class GDIPlusController {
public:
   

    static GDIPlusController& getInstance() {
        static GDIPlusController instance;
        return instance;
    }
    ~GDIPlusController();
private:
    
    GDIPlusController();

   
    ULONG_PTR gdiplusToken;
};

//void initPicture();
void initGDIPlus();