#include "GDIPlusController.h"

GDIPlusController::GDIPlusController() {
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

GDIPlusController::~GDIPlusController() {
    GdiplusShutdown(gdiplusToken);
}

void initGDIPlus() {
    GDIPlusController::getInstance();
}