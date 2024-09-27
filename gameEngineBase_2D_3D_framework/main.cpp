
#include "_conditions.h"

#ifndef _gAPP_test_

#include "windowSystem.h"
#include <iostream>
#include <exception>


// ---------------------------------------*****
// [T E S T]                              *****
// Function for multiple window procedure *****
//                                        *****
// ---------------------------------------*****

#ifdef _TEST_
WindowProcedureFunction(cwndproc_1) {

	static std::chrono::time_point<std::chrono::system_clock> start =
		std::chrono::system_clock::now();
	static std::chrono::duration<double> duration;
	static std::chrono::duration<double> durationPrev;
	durationPrev = duration;
	duration = std::chrono::system_clock::now() - start;

	if (duration.count() > durationPrev.count()+0.01) {
		win.setTitle(std::to_string(duration.count()).c_str());
#ifdef _DEBUG_INFO_
		OutputDebugStringA((std::to_string(duration.count()) + "\n").c_str());
#endif
	}
	
}
#endif



int WINAPI WinMain(HINSTANCE handler, HINSTANCE someTrashMaybe, LPSTR cmdParams, int wndStatus) {
	

	base_window a("newWin", 500, 500, -1, -1);

#ifdef _TEST_
	base_window b("newWin2", 300, 300, 100, 100, cwndproc_1);
	base_window c("newWin3", 300, 400, 100, 500);

	b.setPosition(2000, 1000);
	c.setSize(1000, 1000);
#endif

#ifdef _DEBUG_INFO_
	try {

		base_window::processWindows();
	}
	catch (std::exception& ex) { OutputDebugStringA(ex.what()); }
	base_window::clearWindowList();
#else
	base_window::processWindows();
	base_window::clearWindowList();
#endif
	return 0;
}


#endif // !_gAPP_test_

#ifdef _gAPP_test_

//#define _STREAMING_TEST_

#include "gApp.h"
#include <string>
#include <cmath>
class MyGame : public gAPP {

	//Sprite* s = nullptr;
	Sprite* s1 = nullptr;
	//Sprite* s2;
	//Sprite* s3;
	int v1, v2;
	float a = 25;
	float acc = 0.0f;
	int x = 400, y = 350;
	
	bool 
		
		f = 0, 
		b = 0, 
		l = 0, 
		r = 0, 
		scaleUp = 0, 
		scaleDown = 0;
	


	void initFrameworkResources() override{
	
	}
	void init() override {

		s1 = createSprite("Sprites\\photo_2024-08-20_15-43-51.jpg");
		
		 //setSpritePosition(s1,x, y);
		 getSpriteSize(s1, v1, v2);
	
		 makeSpriteVisible(s1,true);
	}
	void tick() override {

		//setSpritePosition(s1, width / 2 - v1/2, height / 2 - v2/2+a*sin(acc));
		//setSpriteSize(s1, v1 / 2.0f + a * sin(acc), v2 / 2.0f+ a * sin(acc));
		//acc+=0.2f;
		int k = 20;
		if (f) y -= k;
		if (b) y += k;
		if (l) x -= k;
		if (r) x += k;
		setSpritePosition(s1, x, y);

		if (scaleUp) { v1 += 20; v2 += 20; scaleUp = 0; }
		if (scaleDown) { v1 -= 20; v2 -= 20; scaleDown = 0; }
		setSpriteSize(s1,v1, v2);
	}
	void gKeyPressed(gKey k) override { 
		switch (k) {
		case ForwardKey:
			f = 1;
			break;
		case BackwardKey:
			b = 1;
			break;
		case LeftKey:
			l = 1;
			break;
		case RightKey:
			r = 1;
			break;
		}
		//setSpritePosition(s1, 100, 100);
	}
	void mouseKeyPressed(mouseKey k) override {
		switch (k){
	case WheelUp:
		scaleUp = 1;
		break;
	case WheelDown:
		scaleDown = 1;
		break;
	}
	}
	void gKeyReleased(gKey k) override {
		switch (k) {
		case ForwardKey:
			f = 0;
			break;
		case BackwardKey:
			b = 0;
			break;
		case LeftKey:
			l = 0;
			break;
		case RightKey:
			r = 0;
			break;
		}
		//setSpritePosition(s1, 400, 100);
	}
	void mouseKeyReleased(mouseKey k) override {
		
	}
	void mousePosition(int x,int y) override {
	}
	void charInput(char symbol) {

	}
	~MyGame() {
		delete s1;
		//delete s1;
		//delete s2;
		//delete s3;
	}
};

_MAIN_DECL_{

	
	return runApp(new MyGame);
	
}

#endif // _gAPP_test_





