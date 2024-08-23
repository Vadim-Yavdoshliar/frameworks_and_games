
#ifndef _PRECOMPILE_STUFF_
#define _PRECOMPILE_STUFF_


#define _DEBUG_INFO_
//#define _TEST_
#define _gAPP_test_


#define myEXC(errorText) throw std::exception(("\n\n\n\n" + std::string(errorText)+"\n\n\n\n").c_str());
#define myBoxMessage(message,errorType) MessageBoxA(gw_object->getWND(),message,errorType,MB_OK);



#include <Windows.h>
#include <list>
#include <queue>
#include <vector>
#include <ctime>
#include <string>
#include <chrono>
#include <set>
#include <d3d11.h>
#pragma comment (lib,"d3d11")
#include <wrl.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib, "Gdiplus.lib")

#include <d3dcompiler.h>
#pragma comment (lib, "d3dcompiler.lib")

class base_window;

namespace COM = Microsoft::WRL;

#endif